#ifndef TILE_MAP_H_
#define TILE_MAP_H_

#include <vector>
#include <SDL.h>

#include "Tile.h"
#include "TileSet.h"
#include "Rect.h"
#include "rapidxml_utils.hpp"

class TileMap
{
public:
	TileMap();
	~TileMap();

	void free();

	void loadMap(std::string file, SDL_Renderer* renderer);

	void update();
	void render();

private:
	std::vector<TileSet*> vTileSets_;
	std::vector<Tile*> vTiles_;

	int width_;
	int height_;

	SDL_Renderer* renderer_;
};

#endif