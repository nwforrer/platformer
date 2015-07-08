#include "Game.h"

bool Game::init(std::string title, int width, int height)
{
	bool success = true;

	width_ = width;
	height_ = height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// TODO: logging
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window_ == NULL)
		{
			// TODO: logging
			printf("Window could not be create! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer_ == NULL)
			{
				// TODO: logging
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// TODO: initialize SDL_image, SDL_ttf, SDL_mixer
			}
		}
	}

	running_ = true;

	return success;
}

void Game::close()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	window_ = NULL;
	renderer_ = NULL;

	// TODO: close SDL_image, SDL_ttf, SDL_mixer
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				quit();
			} break;

			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						quit();
					} break;
				}
			} break;
		}
	}
}

void Game::update()
{

}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
	SDL_RenderClear(renderer_);

	SDL_RenderPresent(renderer_);
}