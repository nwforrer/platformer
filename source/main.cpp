#include <iostream>

#include "Game.h"

int main(int argc, char **argv)
{
	Game game;

	if (!game.init("Platformer", 1024, 768))
	{
		// TODO: logging
		std::cout << "Failed to initialize!\n";;
	}
	else
	{
		while (game.isRunning())
		{
			game.handleEvents();
			game.update();
			game.render();
		}
	}

	game.close();

	return 0;
}