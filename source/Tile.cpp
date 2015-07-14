#include "Tile.h"

Tile::Tile(TileSet* tileSet, int id, Rect pos, Rect clip, SDL_Renderer* renderer)
{
	tileSet_ = tileSet;
	tileId_ = id;
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

void Tile::update(float timeStep)
{
	currentFrameDuration_ += timeStep;
	if (currentFrameDuration_ >= tileSet_->getAnimationDuration(tileId_, currentFrame_))
	{
		currentFrameDuration_ = 0;

		if (++currentFrame_ >= tileSet_->getNumFrames(tileId_))
			currentFrame_ = 0;
	}
}

void Tile::render()
{
	if (tileSet_->getNumFrames(tileId_) > 0)
	{
		Rect currentFrameClip = tileSet_->getCurrentFrameClip(tileId_, currentFrame_);
		tileSet_->getTexture()->render(pos_, currentFrameClip);
	}
	else
	{
		tileSet_->getTexture()->render(pos_, clip_);
	}
}