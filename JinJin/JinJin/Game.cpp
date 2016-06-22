#include "Game.h"
#include <iostream>

/* D�finition constante du temps d'une frame*/


Game::Game() : window(sf::VideoMode(1600, 900), "Jin Jin"), evHandler(), world(window, evHandler)
{

}

/* On s'assure d'avoir un temps constant entre chque frame*/
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
		
	}
}

void Game::processEvents()
{
	CommandQueue& commands = world.getCommandQueue();

	sf::Event event;
	while (window.pollEvent(event))
	{
		evHandler.handleEvent(event, commands);
		if(event.type == sf::Event::Closed)
		{
			window.close();
		}
	}

	evHandler.handleRealtimeInput(commands);
}


void Game::update(sf::Time deltaTime)
{
	world.update(deltaTime);
}

void Game::render()
{
	window.clear();
	world.draw();

	window.setView(window.getDefaultView());
	window.display();
}

