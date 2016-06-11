#pragma once
#include <SFML\Graphics.hpp>

#include "Command.h"

class CommandQueue;

class EventHandler
{
public:
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

};

