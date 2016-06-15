#pragma once
#include <SFML\Graphics.hpp>

#include "Command.h"

class CommandQueue;

/* Classe de gestion des �venements (inputs ou �venements provoqu�s) */
class EventHandler
{
public:
	EventHandler();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	void addDrawText(const sf::String str);

private:
	bool jumping;

	bool displaying;

	sf::Time jumpTime;

	sf::Time textTime;
	sf::String textString;
};

