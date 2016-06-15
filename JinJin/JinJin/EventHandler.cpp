#include "EventHandler.h"
#include "CommandQueue.h"
#include "Player.h"
#include "Plateform.h"
#include "Shadow.h"

#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

/* Simplification de l'appel à setVelocity */
struct PlayerMover
{
	PlayerMover(float vx, float vy) : velocity(vx,vy){ }

	void operator() (Player& player, sf::Time) const
	{
		player.setVelocity(player.getVelocity() + velocity);
	}

	sf::Vector2f velocity;
};

EventHandler::EventHandler() : jumping(false)
{
}

/* Gestion des évenements demandés*/
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
	/* Demande aux plateformes de s'inverser (les ombres deviennent materielle et les plateformes non)*/
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

/* Gestion des evenements de déplacement*/
void EventHandler::handleRealtimeInput(CommandQueue & commands)
{
	const float playerspeed = 200.f;
	
	/* Saut */
	if(jumping)
	{
		jumpTime += TimePerFrame;
		if (jumpTime.asSeconds() < 0.5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			Command moveUp;
			moveUp.category = Category::Player;
			moveUp.action = derivedAction<Player>([playerspeed](Player& player, sf::Time) {
					player.jump(playerspeed);
			});
			commands.push(moveUp);
		} else
		{
			jumping = false;
			Command endJump;
			endJump.category = Category::Player;
			endJump.action = derivedAction<Player>([playerspeed](Player& player, sf::Time) {
				player.setJumping(false);
			});
			commands.push(endJump);
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		//si le joueur est au sol et qu'il ne saute pas il peut rentrer dans la phacse saut
		if (!jumping)
		{
			jumping = true;
			jumpTime = sf::Time::Zero;
		}
		
	}
	/* Gauche */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(-0.75*playerspeed, 0.f));
		commands.push(moveUp);
	}
	/* Droite */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Command moveUp;
		moveUp.category = Category::Player;
		moveUp.action = derivedAction<Player>(PlayerMover(0.75*playerspeed, 0.f));
		commands.push(moveUp);
	}
}
