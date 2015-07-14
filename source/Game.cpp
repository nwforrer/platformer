#include "Game.h"
#include "TileSet.h"

bool Game::init(std::string title, int width, int height)
{
	bool success = true;

	width_ = width;
	height_ = height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// TODO: logging
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << '\n';
		success = false;
	}
	else
	{
		window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window_ == NULL)
		{
			// TODO: logging
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << '\n';
			success = false;
		}
		else
		{
			renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer_ == NULL)
			{
				// TODO: logging
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << '\n';
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					// TODO: logging
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';
				}
				
				// TODO: initialize SDL_ttf, SDL_mixer
			}
		}
	}

	loadMedia_();

	running_ = true;

	gameTimer_.start();
	countedFrames_ = 0;

	return success;
}

void Game::close()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	window_ = NULL;
	renderer_ = NULL;

	for (auto iter : textures_)
	{
		iter.second->free();
		delete iter.second;
	}

	for (auto gameObject : gameObjects_)
	{
		gameObject->free();
		delete gameObject;
	}

	// TODO: close SDL_ttf, SDL_mixer
	IMG_Quit();
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
	float timeStep = gameTimer_.getDeltaTicks();
	// float avgFPS = countedFrames_ / (gameTimer_.getTicks() / 1000.0f);
	// if (avgFPS > 2000000)
	// {
	// 	avgFPS = 0;
	// }

	// std::cout << "FPS: " << avgFPS << '\n';

	for (GameObject* gameObject : gameObjects_)
	{
		gameObject->update();
	}

	tileMap_.update(timeStep);
	// ++countedFrames_;
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
	SDL_RenderClear(renderer_);

	for (GameObject* gameObject : gameObjects_)
	{
		gameObject->render();
	}

	tileMap_.render();

	SDL_RenderPresent(renderer_);
}

bool Game::loadMedia_()
{
	tileMap_.loadMap("untitled.tmx", renderer_);

	return true;
}