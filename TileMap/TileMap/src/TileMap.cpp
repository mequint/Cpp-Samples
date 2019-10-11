#include "TileMap.h"

#include <iostream>
#include <sstream>

TileMap::TileMap() : m_tileSize(0), m_width(0), m_height(0) {
}

bool TileMap::LoadFromFile(const std::string& filename) {
	std::ifstream file(filename.c_str());

	if (!file.is_open()) {
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream stream(line);
		std::string type;
		stream >> type;

		if (type == "TileSize") {
			stream >> m_tileSize;
		}
		else if (type == "MapSize") {
			stream >> m_width >> m_height;
			m_mapData.reserve(m_width * m_height);
		}
		else if (type == "PalleteSize") {
			stream >> m_palleteSize;
			m_palette.reserve(m_palleteSize);
		}
		else if (type == "Pallete") {
			if (m_palleteSize <= 0) {
				std::cout << "ERROR: PaletteSize has not been set" << std::endl;
				return false;
			}

			for (int i = 0; i < m_palleteSize; ++i) {
				std::string tile;

				if (std::getline(file, tile)) {
					std::stringstream tilestream(tile);

					std::string tileName;
					int tileId;
					bool isSolid;
					tilestream >> tileName >> tileId >> isSolid;

					m_palette.emplace_back(tileName, tileId, isSolid);
				}
			}
		}
		else if (type == "MapData") {
			if (m_width <= 0 || m_height <= 0) {
				std::cout << "ERROR: MapSize has not been set" << std::endl;
				return false;
			}

			std::string indexDelimiter = ",";
			int heightIndex = 0;

			while (heightIndex < m_height) {
				heightIndex++;
			}

			for (int i = 0; i < m_height; ++i) {
				std::string row;
				if (std::getline(file, row)) {
					size_t pos = 0;
					int x = 0;
					while (x < m_width) {
						pos = row.find(indexDelimiter);
						int tile = -1;
						if (pos != std::string::npos) {
							tile = std::stoi(row.substr(0, pos));
							row.erase(0, pos + indexDelimiter.length());
						}
						else {
							tile = std::stoi(row);
							m_mapData.push_back(tile);
							break;
						}

						m_mapData.push_back(tile);
						++x;
					}
				}
			}
		}
	}

	file.close();

	return true;
}

int TileMap::GetTileSize() const { return m_tileSize; }
int TileMap::GetWidth() const { return m_width; }
int TileMap::GetHeight() const { return m_height; }

int TileMap::GetMapTile(int x, int y) const {
	return m_mapData[y * m_width + x];
}

Tile TileMap::GetTileData(int id) const {
	return m_palette[id];
}
