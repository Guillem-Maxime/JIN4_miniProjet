#pragma once
#include <SFML\Graphics.hpp>

#include "Command.h"

class CommandQueue;

/* Classe de gestion des évenements (inputs ou évenements provoqués) */
class EventHandler
{
public:
	EventHandler();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	void addDrawText(const sf::String str, int size);

	void addInverse();

private:
	bool jumping;

	bool displaying;

	bool inversed;

	sf::Time jumpTime;

	sf::Time textTime;
	sf::String textString;
	int textSize;
};

