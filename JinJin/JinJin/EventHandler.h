#pragma once
#include <SFML\Graphics.hpp>

#include "Command.h"

class CommandQueue;

/* Classe de gestion des évenements (inputs ou évenements provoqués) */
class EventHandler
{
public:
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

};

