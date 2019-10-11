#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Tile.h"

using TileMapData = std::vector<int>;
using Pallete = std::vector<Tile>;

class TileMap {
public:
	TileMap();
	bool LoadFromFile(const std::string& filename);
	
	int GetTileSize() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetMapTile(int x, int y) const;
	Tile GetTileData(int id) const;

private:
	int m_tileSize;
	int m_width;
	int m_height;
	TileMapData m_mapData;

	int m_palleteSize;
	Pallete m_palette;
};