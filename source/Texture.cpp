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
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << '\n';
	}
	else
	{
		texture_ = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (texture_ == NULL)
		{
			// TODO: logging
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << '\n';
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

void Texture::render(int x, int y, double scale, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, (int)(scale*width_), (int)(scale*height_) };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer_, texture_, clip, &renderQuad);
}

void Texture::render(Rect pos, Rect clip)
{
	SDL_Rect renderQuad = { pos.x, pos.y, pos.w, pos.h };
	SDL_Rect clipQuad = { clip.x, clip.y, clip.w, clip.h };

	SDL_RenderCopy(renderer_, texture_, &clipQuad, &renderQuad);
}