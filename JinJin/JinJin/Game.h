#pragma once
#include <SFML\Graphics.hpp>
#include "World.h"
#include "EventHandler.h"

/* Boucle de rendu*/
class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

private:
	sf::RenderWindow window;
	
	World world;
	EventHandler evHandler;

};