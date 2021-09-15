#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Tile.h"

using TileMapData = std::vector<int>;
using Pallete = std::vector<Tile>;

struct Warp {
	std::string MapName;
	int FromX, FromY;
	int ToX, ToY;
};

using WarpList = std::vector<Warp>;

class TileMap {
public:
	TileMap();
	bool loadFromFile(const std::string& filename);
	bool loadFromJsonFile(const std::string& filename);

	int getTileSize() const;
	int getWidth() const;
	int getHeight() const;
	int getMapTile(int x, int y) const;
	Tile getTileData(int id) const;

	Warp getWarpData(int x, int y) const;

private:
	int m_tileSize;
	int m_width;
	int m_height;
	TileMapData m_mapData;

	Pallete m_palette;

	WarpList m_warps;
};