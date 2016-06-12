#include "EventHandler.h"
#include "CommandQueue.h"
#include "Player.h"
#include "Plateform.h"
#include "Shadow.h"

#include <iostream>



struct PlayerMover
{
	PlayerMover(float vx, float vy) : velocity(vx,vy){ }

	void operator() (Player& player, sf::Time) const
	{
		player.setVelocity(player.getVelocity() + velocity);
	}

	sf::Vector2f velocity;
};


void EventHandler::handleEvent(const sf::Event & event, CommandQueue & commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::Player;
		output.action = [](SceneNode& s, sf::Time){
			std::cout << s.getPosition().x << "," << s.getPosition().y << std::endl;
		};
		commands.push(output);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
	{
		Command output;
		output.category = Category::Platform;
		output.action = derivedAction<Plateform>([](Plateform& plateform, sf::Time) {
			plateform.inverse();
		});
		commands.push(output);
		Command output2;
		output2.category = Category::Shadow;
		output2.action = derivedAction<Shadow>([](Shadow& shadow, sf::Time) {
			shadow.inverse();
		});
		commands.push(output2);
	}
}

void EventHandler::handleRealtimeInput(CommandQueue & commands)
{
	const float playerspeed = 10.f;

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>([playerspeed](Player& player, sf::Time) {
			player.jump(playerspeed);
		});
		commands.push(moveUp);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(-0.75*playerspeed, 0.f));
		commands.push(moveUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(0.75*playerspeed, 0.f));
		commands.push(moveUp);
	}
}
