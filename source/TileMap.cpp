#include "TileMap.h"

TileMap::TileMap()
{
	width_ = 0;
	height_ = 0;

	renderer_ = NULL;
}

TileMap::~TileMap()
{
	free();
}

void TileMap::free()
{
	for (TileSet* tileSet : vTileSets_)
	{
		tileSet->free();
		delete tileSet;
	}

	for (Tile* tile : vTiles_)
	{
		delete tile;
	}
}

void TileMap::loadMap(std::string file, SDL_Renderer* renderer)
{
	free();

	renderer_ = renderer;

	rapidxml::file<> xmlFile(file.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	auto *root = doc.first_node();

	int mapWidth = atoi(root->first_attribute("width")->value());
	int mapHeight = atoi(root->first_attribute("height")->value());

	for (auto *tileSetNode = root->first_node("tileset");
		tileSetNode;
		tileSetNode = tileSetNode->next_sibling("tileset"))
	{
		int firstgid = atoi(tileSetNode->first_attribute("firstgid")->value());
		std::string name = tileSetNode->first_attribute("name")->value();
		int tileWidth = atoi(tileSetNode->first_attribute("tilewidth")->value());
		int tileHeight = atoi(tileSetNode->first_attribute("tileheight")->value());

		auto imageNode = tileSetNode->first_node("image");
		std::string source = imageNode->first_attribute("source")->value();
		int imageWidth = atoi(imageNode->first_attribute("width")->value());
		int imageHeight = atoi(imageNode->first_attribute("height")->value());

		vTileSets_.push_back(new TileSet(renderer, firstgid, name, tileWidth, tileHeight,
										source, imageWidth, imageHeight));
	}

	std::vector<std::vector<int>> vTileIds;

	for (auto *layerNode = root->first_node("layer");
		layerNode;
		layerNode = layerNode->next_sibling("layer"))
	{
		std::vector<int> vLayerTileIds;
		std::string layerName = layerNode->first_attribute("name")->value();

		for (auto *tileNode = layerNode->first_node("data")->first_node("tile");
			tileNode;
			tileNode = tileNode->next_sibling("tile"))
		{
			int gid = atoi(tileNode->first_attribute("gid")->value());

			//if (gid > 0)
			//{
				vLayerTileIds.push_back(gid);
			//}
		}
		vTileIds.push_back(vLayerTileIds);
	}

	for (std::vector<int> vLayerTileIds : vTileIds)
	{
		for (int tileX = 0;
			tileX < mapWidth;
			++tileX)
		{
			for (int tileY = 0;
				tileY < mapHeight;
				++tileY)
			{
				unsigned int gid = vLayerTileIds[(tileX + (tileY*mapWidth))];
				
				if (gid == 0)
					continue;

				for (auto i = vTileSets_.rbegin();
					i != vTileSets_.rend();
					++i)
				{
					TileSet* tileSet = *i;
					int numOfCols = tileSet->getImageWidth() / tileSet->getTileWidth();
					if (gid >= tileSet->getFirstGid())
					{
						int tileSetCol = (gid-tileSet->getFirstGid()) % numOfCols;
						int tileSetRow = (gid-tileSet->getFirstGid()) / numOfCols;

						Rect pos;
						pos.x = tileX * tileSet->getTileWidth();
						pos.y = tileY * tileSet->getTileHeight();
						pos.w = tileSet->getTileWidth();
						pos.h = tileSet->getTileHeight();

						Rect clip;
						clip.x = tileSet->getTileWidth() * tileSetCol;
						clip.y = tileSet->getTileHeight() * tileSetRow;
						clip.w = tileSet->getTileWidth();
						clip.h = tileSet->getTileHeight();

						vTiles_.push_back(new Tile(tileSet, pos, clip, renderer));
						break;
					}
				}
			}
		}
	}
}

void TileMap::render()
{
	for (Tile* tile : vTiles_)
	{
		tile->render();
	}
}