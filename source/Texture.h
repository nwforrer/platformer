#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "Rect.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFromFile(SDL_Renderer* renderer, std::string path);

	void free();
	void render(int x, int y, double scale, SDL_Rect* clip = NULL);
	void render(Rect pos, Rect clip);

	int getWidth() { return width_; }
	int getHeight() { return height_; }

private:
	SDL_Texture* texture_;
	SDL_Renderer* renderer_;

	int width_;
	int height_;
};

#endif