#include "Tile.h"

Tile::Tile(TileSet* tileSet, Rect pos, Rect clip, SDL_Renderer* renderer)
{
	tileSet_ = tileSet;
	tileWidth_ = tileSet_->getTileWidth();
	tileHeight_ = tileSet_->getTileHeight();

	pos_ = pos;
	clip_ = clip;

	renderer_ = renderer;
}

Tile::~Tile()
{

}

void Tile::render()
{
	tileSet_->getTexture()->render(pos_, clip_);
}