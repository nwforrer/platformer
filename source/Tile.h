#ifndef TILE_H_
#define TILE_H_

#include <SDL.h>
#include "TileSet.h"
#include "Rect.h"

class Tile
{
public:
	Tile(TileSet* tileSet, Rect pos, Rect clip, SDL_Renderer* renderer);
	~Tile();

	void render();

private:
	TileSet* tileSet_;
	Rect pos_;
	Rect clip_;
	int tileWidth_;
	int tileHeight_;

	SDL_Renderer* renderer_;
};

#endif