#include "Game.h"
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : window(sf::VideoMode(1600, 900), "Jin Jin"), world(window), evHandler()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		processEvents();
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

