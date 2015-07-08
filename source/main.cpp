#include <cstdio>

#include "Game.h"

int main(int argc, char **argv)
{
	Game game;

	if (!game.init("Platformer", 640, 480))
	{
		// TODO: logging
		printf("Failed to initialize!\n");
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