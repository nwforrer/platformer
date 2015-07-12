#include "Tile.h"

Tile::Tile(TileSet* tileSet, Rect pos, Rect clip, SDL_Renderer* renderer)
{
	tileSet_ = tileSet;
	tileWidth_ = tileSet_->getTileWidth();
	tileHeight_ = tileSet_->getTileHeight();

	pos_ = pos;
	clip_ = clip;

	currentFrame_ = 0;

	renderer_ = renderer;
}

Tile::~Tile()
{

}

void Tile::update()
{
	if (++currentFrameDuration_ >= tileSet_->getAnimationDuration())
	{
		currentFrameDuration_ = 0;

		if (++currentFrame_ >= tileSet_->getNumFrames())
			currentFrame_ = 0;
	}
}

void Tile::render()
{
	if (tileSet_->getNumFrames() > 0)
	{
		Rect currentFrameClip = tileSet_->getCurrentFrameClip(currentFrame_);
		tileSet_->getTexture()->render(pos_, currentFrameClip);
	}
	else
	{
		tileSet_->getTexture()->render(pos_, clip_);
	}
}