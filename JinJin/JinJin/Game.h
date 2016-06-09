#pragma once
#include <SFML\Graphics.hpp>
#include "TextureHolder.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update(sf::Time deltaTime);
	void render();

private:
	sf::RenderWindow window;
	TextureHolder textures;
	sf::Sprite player;

	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;

	int speed;
};