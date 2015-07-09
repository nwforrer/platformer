#include "Game.h"

#include "rapidxml_utils.hpp"

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
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					// TODO: logging
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				}
				
				// TODO: initialize SDL_ttf, SDL_mixer
			}
		}
	}

	loadMedia_();

	running_ = true;

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
	for (GameObject* gameObject : gameObjects_)
	{
		gameObject->update();
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);
	SDL_RenderClear(renderer_);

	for (GameObject* gameObject : gameObjects_)
	{
		gameObject->render();
	}

	SDL_RenderPresent(renderer_);
}

bool Game::loadMedia_()
{
	rapidxml::file<> xmlFile("map.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *pRoot = doc.first_node();

	// load all textures into memory
	for (rapidxml::xml_node<> *pTextureNode=pRoot->first_node("texture"); pTextureNode; pTextureNode=pTextureNode->next_sibling("texture"))
	{
		rapidxml::xml_attribute<> *pIdAttr = pTextureNode->first_attribute("id");
		int id = atoi(pIdAttr->value());

		if (textures_.find(id) == textures_.end())
		{
			Texture* texture = new Texture;

			rapidxml::xml_attribute<> *pFileAttr = pTextureNode->first_attribute("file");

			texture->loadFromFile(renderer_, pFileAttr->value());
			textures_[id] = texture;
		}
	}

	// load all game objects
	for (rapidxml::xml_node<> *pObjectNode=pRoot->first_node("object"); pObjectNode; pObjectNode=pObjectNode->next_sibling("object"))
	{
		GameObject* gameObject = new GameObject;

		rapidxml::xml_attribute<> *pXAttr = pObjectNode->first_attribute("x");
		rapidxml::xml_attribute<> *pYAttr = pObjectNode->first_attribute("y");

		gameObject->x = atoi(pXAttr->value());
		gameObject->y = atoi(pYAttr->value());

		for (rapidxml::xml_node<> *pComponent=pObjectNode->first_node("component"); pComponent; pComponent=pComponent->next_sibling("component"))
		{
			rapidxml::xml_attribute<> *pNameAttr = pComponent->first_attribute("name");
			if (strcmp(pNameAttr->value(), "sprite") == 0)
			{
				// the texture id corresponds to the previously loaded textures
				rapidxml::xml_attribute<> *pTextureIdAttr = pComponent->first_attribute("textureId");
				int textureId = atoi(pTextureIdAttr->value());
				
				rapidxml::xml_attribute<> *pScaleAttr = pComponent->first_attribute("scale");
				double scale = 1.0d;
				if (pScaleAttr != 0)
				{
					scale = atof(pScaleAttr->value());
				}

				gameObject->init(new SpriteComponent(textures_[textureId], scale));
			}
		}

		gameObjects_.push_back(gameObject);
	}

	return true;
}