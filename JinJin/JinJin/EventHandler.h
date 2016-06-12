#pragma once
#include <SFML\Graphics.hpp>

#include "Command.h"

class CommandQueue;

/* Classe de gestion des �venements (inputs ou �venements provoqu�s) */
class EventHandler
{
public:
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

};

