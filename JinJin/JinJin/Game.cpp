#include "Game.h"
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : window(sf::VideoMode(1600, 900), "Jin Jin"), textures(), player()
{
	textures.load(Textures::Player, "Media/Sprites/1.png");

	player.setTexture(textures.get(Textures::Player));
	player.setPosition(500.f, 200.f);

	speed = 400;
	isDown = false; isUp = false; isRight = false; isLeft = false;
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
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Z)
		isUp = isPressed;
	else if (key == sf::Keyboard::S)
		isDown = isPressed;
	else if (key == sf::Keyboard::Q)
		isLeft = isPressed;
	else if (key == sf::Keyboard::D)
		isRight = isPressed;

}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (isUp)
		movement.y -= speed;
	if (isDown)
		movement.y += speed;
	if (isLeft)
		movement.x -= speed;
	if (isRight)
		movement.x += speed;

	player.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	window.clear();
	window.draw(player);
	window.display();
}

