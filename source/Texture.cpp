#include "Texture.h"

Texture::Texture()
{
	texture_ = NULL;
	renderer_ = NULL;

	width_ = 0;
	height_ = 0;
}

Texture::~Texture()
{
	free();
}

void Texture::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	free();

	renderer_ = renderer;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		// TODO: logging
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		texture_ = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (texture_ == NULL)
		{
			// TODO: logging
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			width_ = loadedSurface->w;
			height_ = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	return texture_ != NULL;
}

void Texture::render(int x, int y, double scale)
{
	SDL_Rect renderQuad = { x, y, (int)(scale*width_), (int)(scale*height_) };
	SDL_RenderCopy(renderer_, texture_, NULL, &renderQuad);
}