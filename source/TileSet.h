#ifndef TILE_SET_H_
#define TILE_SET_H_

#include <SDL.h>
#include <math.h>
#include <vector>
#include <map>
#include "Texture.h"
#include "Rect.h"

class TileSet
{
public:
	TileSet(SDL_Renderer* renderer, unsigned int firstgid, std::string name, unsigned int tileWidth, unsigned int tileHeight,
		std::string source, unsigned int imageWidth, unsigned int imageHeight);
	~TileSet();

	void free();

	void addAnimationFrame(int sourceTileId, int tileId, int duration);

	Rect getCurrentFrameClip(int sourceTileId, int currentFrame);

	unsigned int getFirstGid() const { return firstgid_; }
	unsigned int getLastGid() const { return lastgid_; }
	unsigned int getTileWidth() const { return tileWidth_; }
	unsigned int getTileHeight() const { return tileHeight_; }
	unsigned int getImageWidth() const { return imageWidth_; }
	unsigned int getImageHeight() const { return imageHeight_; }
	unsigned int getTileAmountWidth() const { return tileAmountWidth_; }
	Texture* getTexture() const { return texture_; }

	unsigned int getNumFrames(int sourceTileId);

	unsigned int getAnimationDuration() const { return animationDuration_; }
	
private:
	SDL_Renderer* renderer_;
	Texture* texture_;
	unsigned int firstgid_;
	unsigned int lastgid_;
	std::string name_;
	unsigned int tileWidth_;
	unsigned int tileHeight_;
	unsigned int imageWidth_;
	unsigned int imageHeight_;
	std::string source_;
	unsigned int tileAmountWidth_;

	std::map<int, std::vector<int>> vFrameIds_;
	unsigned int animationDuration_;
};

#endif