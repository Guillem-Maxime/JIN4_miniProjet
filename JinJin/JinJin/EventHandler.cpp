#include "EventHandler.h"
#include "CommandQueue.h"
#include "Player.h"

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
}

void EventHandler::handleRealtimeInput(CommandQueue & commands)
{
	const float playerspeed = 30.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(0.f, -playerspeed));
		commands.push(moveUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(0.f, playerspeed));
		commands.push(moveUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(-playerspeed, 0.f));
		commands.push(moveUp);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(playerspeed, 0.f));
		commands.push(moveUp);
	}
}
