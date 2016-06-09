#include "Game.h"
#include <iostream>

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nERREUR: " << e.what() << std::endl;
	}
}