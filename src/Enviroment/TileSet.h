#pragma once

#include "SDL_Enviroment.h"

#include "utils/Math/Math.h"

#include <unordered_map>





struct TileSet
{
	std::vector<SDL_Rect> srcRects;
	Vector2i grid;
	Vector2i tileDim;
};



class TileSetHandler
{
public:
	TileSetHandler() {}

	TileSet* getTileSet(const std::string& path);
	TileSet* loadTileSet(const std::string& path);

protected:
	std::unordered_map<std::string, TileSet*> mTileSets;
};