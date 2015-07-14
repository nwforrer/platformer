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

void TileSet::addAnimationFrame(int sourceTileId, int tileId, int duration)
{
	if (vFrameIds_.count(sourceTileId) == 0)
	{
		vFrameIds_.insert(std::pair<int, std::vector<AnimationFrameData>>(sourceTileId, std::vector<AnimationFrameData>()));
	}

	vFrameIds_.at(sourceTileId).push_back(AnimationFrameData(tileId, duration));
}

Rect TileSet::getCurrentFrameClip(int sourceTileId, int currentFrame)
{
	Rect clip;

	if (vFrameIds_.count(sourceTileId) > 0)
	{
		std::vector<AnimationFrameData> tileFrames = vFrameIds_.at(sourceTileId);

		int numOfCols = imageWidth_ / tileWidth_;
		int tileSetCol = tileFrames[currentFrame].getTileId() % numOfCols;
		int tileSetRow = tileFrames[currentFrame].getTileId() / numOfCols;

		clip.x = tileWidth_ * tileSetCol;
		clip.y = tileHeight_ * tileSetRow;
		clip.w = tileWidth_;
		clip.h = tileHeight_;
	}

	return clip;
}

unsigned int TileSet::getNumFrames(int sourceTileId)
{
	unsigned int numFrames = 0;

	if (vFrameIds_.count(sourceTileId))
	{
		numFrames = vFrameIds_.at(sourceTileId).size();
	}

	return numFrames;
}

unsigned int TileSet::getAnimationDuration(int sourceTileId, int currentFrame)
{
	unsigned int duration = 0;

	if (vFrameIds_.count(sourceTileId))
	{
		duration = vFrameIds_.at(sourceTileId).at(currentFrame).getDuration();
	}

	return duration;
}
