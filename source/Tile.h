#ifndef TILE_H_
#define TILE_H_

#include <SDL.h>

#include <vector>

#include "TileSet.h"
#include "Texture.h"
#include "Rect.h"

class Tile
{
public:
	Tile(TileSet* tileSet, int id, Rect pos, Rect clip, SDL_Renderer* renderer);
	~Tile();

	void update(float timeStep);
	void render();

private:
	TileSet* tileSet_;
	unsigned int tileId_;
	Rect pos_;
	Rect clip_;
	unsigned int tileWidth_;
	unsigned int tileHeight_;

	unsigned int currentFrame_;
	unsigned int currentFrameDuration_;

	SDL_Renderer* renderer_;
};

#endif