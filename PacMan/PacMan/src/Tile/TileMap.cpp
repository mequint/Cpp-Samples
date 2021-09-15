#include "Tile/TileMap.h"

#include <algorithm>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>

TileMap::TileMap() : m_tileSize(0), m_width(0), m_height(0) {
}

bool TileMap::loadFromFile(const std::string& filename) {
	std::mutex lock;
	lock.lock();

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
		else if (type == "Pallete") {
			int paletteSize;
			stream >> paletteSize;

			if (paletteSize <= 0) {
				std::cout << "ERROR: Palette Size is invalid" << std::endl;
				return false;
			}

			m_palette.reserve(paletteSize);

			for (int i = 0; i < paletteSize; ++i) {
				std::string tileData;

				if (std::getline(file, tileData)) {
					std::stringstream tilestream(tileData);
					
					Tile tile;
					tilestream >> tile.Name >> tile.Id >> tile.IsSolid >> tile.IsWarp;

					m_palette.emplace_back(tile);
				}
			}
		}
		else if (type == "MapData") {
			stream >> m_width >> m_height;
			m_mapData.reserve(m_width * m_height);

			if (m_width <= 0 || m_height <= 0) {
				std::cout << "ERROR: Map width or height is invalid" << std::endl;
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
		else if (type == "Warps") {
			int warpCount;
			stream >> warpCount;
			
			if (warpCount < 0) {
				std::cout << "ERROR: Warp count cannot be less then 0" << std::endl;
				return false;
			}

			for (int i = 0; i < warpCount; ++i) {
				std::string warpData;
				if (std::getline(file, warpData)) {
					std::stringstream warpStream(warpData);
					Warp warp;

					warpStream >> warp.MapName >> warp.FromX >> warp.FromY >> warp.ToX >> warp.ToY;

					m_warps.emplace_back(warp);
				}
			}
		}
	}

	file.close();
	lock.unlock();

	return true;
}

bool TileMap::loadFromJsonFile(const std::string & filename) {
	std::mutex lock;
	lock.lock();

	std::ifstream jsonFile(filename);

	nlohmann::json json;
	jsonFile >> json;

	jsonFile.close();
	lock.unlock();

	if (json.contains("name") && json["name"].is_string()) {		
		// TODO: Add when multiple maps are used in future games
	}

	if (json.contains("tileSize") && json["tileSize"].is_number_unsigned()) {
		m_tileSize = json["tileSize"].get<unsigned int>();
	}

	if (json.contains("palette") && json["palette"].is_array()) {
		auto jsonPaletteArray = json["palette"];

		for (auto const& jsonPalette : jsonPaletteArray) {
			Tile tile;

			if (jsonPalette.contains("name") && jsonPalette["name"].is_string() &&
				jsonPalette.contains("id") && jsonPalette["id"].is_number_integer() &&
				jsonPalette.contains("isSolid") && jsonPalette["isSolid"].is_boolean() &&
				jsonPalette.contains("isWarp") && jsonPalette["isWarp"].is_boolean()) {

				tile.Name = jsonPalette["name"].get<std::string>();
				tile.Id = jsonPalette["id"].get<int>();
				tile.IsSolid = jsonPalette["isSolid"].get<bool>();
				tile.IsWarp = jsonPalette["isWarp"].get<bool>();

				m_palette.emplace_back(tile);
			}
		}
	}

	if (json.contains("mapData") && json["mapData"].is_object()) {
		auto jsonMapData = json["mapData"].get<nlohmann::json>();

		if (jsonMapData.contains("size") && jsonMapData["size"].is_object()) {
			auto jsonSize = jsonMapData["size"];

			if (jsonSize.contains("width") && jsonSize["width"].is_number_integer() &&
				jsonSize.contains("height") && jsonSize["height"].is_number_integer()) {
				m_width = jsonSize["width"].get<int>();
				m_height = jsonSize["height"].get<int>();

				m_mapData.reserve(m_width * m_height);
			}
		}

		if (jsonMapData.contains("tiles") && jsonMapData["tiles"].is_array()) {
			auto jsonRows = jsonMapData["tiles"];

			for (auto const& tile : jsonRows) {
				if (tile.is_number_integer()) {
					int tileIndex = tile.get<int>();
					m_mapData.push_back(tileIndex);
				}
			}
		}
	}

	if (json.contains("warps")) {
		// TODO: Add when multiple maps are used in future games
	}

	return true;
}

int TileMap::getTileSize() const { return m_tileSize; }
int TileMap::getWidth() const { return m_width; }
int TileMap::getHeight() const { return m_height; }

int TileMap::getMapTile(int x, int y) const {
	return m_mapData[y * m_width + x];
}

Tile TileMap::getTileData(int id) const {
	return m_palette[id];
}

Warp TileMap::getWarpData(int x, int y) const {
	auto warp = std::find_if(m_warps.begin(), m_warps.end(), [x, y](Warp warp) {
		return x == warp.FromX && y == warp.FromY;
	});

	if (warp == m_warps.end()) return Warp();

	return *warp;
}