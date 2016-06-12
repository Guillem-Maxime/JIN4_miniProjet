#pragma once

#include "Command.h"
#include <queue>

/* File contenant les commandes à effectuer pour cet update*/
class CommandQueue
{
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:
	std::queue<Command> queue;

	
};

