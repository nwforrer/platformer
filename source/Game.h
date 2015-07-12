#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <stdlib.h>
#include <vector>
#include <map>

#include "GameObject.h"
#include "TileMap.h"

class Game
{
public:
	bool init(std::string title, int width, int height);
	void close();

	void handleEvents();
	void update();
	void render();

	bool isRunning() { return running_; }
	void quit() { running_ = false; }

	int getWidth() { return width_; }
	int getHeight() { return height_; }

private:

	bool loadMedia_();

	SDL_Window* window_;
	SDL_Renderer* renderer_;

	std::vector<GameObject*> gameObjects_;
	std::map<int, Texture*> textures_;

	TileMap tileMap_;

	int width_;
	int height_;

	bool running_;
};

#endif