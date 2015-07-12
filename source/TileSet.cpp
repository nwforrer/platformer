#include "TileSet.h"

TileSet::TileSet(SDL_Renderer* renderer, unsigned int firstgid, std::string name, unsigned int tileWidth, unsigned int tileHeight,
		std::string source, unsigned int imageWidth, unsigned int imageHeight)
{
	renderer_ = renderer;
	firstgid_ = firstgid;
	name_ = name;
	tileWidth_ = tileWidth;
	tileHeight_ = tileHeight;
	source_ = source;
	imageWidth_ = imageWidth;
	imageHeight_ = imageHeight;
	tileAmountWidth_ = floor(imageWidth / tileWidth);
	lastgid_ = tileAmountWidth_ * floor(imageHeight / tileHeight) + firstgid - 1;

	texture_ = new Texture;
	texture_->loadFromFile(renderer, source);
}

TileSet::~TileSet()
{
	free();
}

void TileSet::free()
{
	if (texture_ != nullptr)
	{
		texture_->free();
		delete texture_;
		texture_ = nullptr;
	}
}
