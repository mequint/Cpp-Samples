#include "Map.h"

#include "DebugOverlay.h"
#include "EntityManager.h"
#include "StateManager.h"
#include "Window.h"

Map::Map(SharedContext * context) :
	m_context(context),
	m_defaultTile(context),
	m_maxMapSize(32, 32),
	m_playerId(-1) {

	m_context->m_gameMap = this;
	LoadTiles("tiles.cfg");
}

Map::~Map() {
	PurgeMap();
	PurgeTileSet();

	m_context->m_gameMap = nullptr;
}

Tile * Map::GetTile(unsigned int x, unsigned int y, unsigned int layer) {
	if (x >= m_maxMapSize.x || y >= m_maxMapSize.y || layer >= Sheet::Num_Layers) {
		return nullptr;
	}

	auto iter = m_tileMap.find(ConvertCoords(x, y, layer));
	if (iter == m_tileMap.end()) return nullptr;

	return iter->second;
}

TileInfo * Map::GetDefaultTile() { return &m_defaultTile; }
unsigned int Map::GetTileSize() const { return Sheet::Tile_Size; }
const sf::Vector2u& Map::GetMapSize() const { return m_maxMapSize; }
const sf::Vector2f& Map::GetPlayerStart() const { return m_playerStart; }
int Map::GetPlayerId() const { return m_playerId; }

void Map::LoadMap(const std::string & path) {
	std::ifstream mapFile;
	mapFile.open(Utils::GetWorkingDirectory() + path);
	if (!mapFile.is_open()) {
		std::cout << "! Failed loading map file: " << path << std::endl;
		return;
	}

	std::string line;
	std::cout << "--- Loading a map: " << path << std::endl;

	while (std::getline(mapFile, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "TILE") {
			int tileId = 0;
			keystream >> tileId;

			if (tileId < 0) {
				std::cout << "! Bad tile id: " << tileId << std::endl;
				continue;
			}

			auto iter = m_tileSet.find(tileId);
			if (iter == m_tileSet.end()) {
				std::cout << "! Tile id(" << tileId << ") was not found in tileset." << std::endl;
				continue;
			}

			sf::Vector2u tileCoords;
			unsigned int tileLayer = 0;
			unsigned int tileSolidity = 0;

			keystream >> tileCoords.x >> tileCoords.y >> tileLayer >> tileSolidity;

			if (tileCoords.x > m_maxMapSize.x || tileCoords.y > m_maxMapSize.y || tileLayer >= Sheet::Num_Layers) {
				std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << " " << tileLayer << std::endl;
				continue;
			}

			Tile* tile = new Tile();
			tile->m_properties = iter->second;
			tile->m_solid = static_cast<bool>(tileSolidity);

			if (!m_tileMap.emplace(ConvertCoords(tileCoords.x, tileCoords.y, tileLayer), tile).second) {
				std::cout << "! Duplicate tile:" << tileCoords.x << " " << tileCoords.y << " " << tileLayer << std::endl;

				delete tile;
				continue;
			}

			std::string warp;
			keystream >> warp;

			tile->m_warp = false;
			if (warp == "WARP") {
				tile->m_warp = true;
			}
		}
		else if (type == "SIZE") {
			keystream >> m_maxMapSize.x >> m_maxMapSize.y;
		}
		else if (type == "DEFAULT_FRICTION") {
			keystream >> m_defaultTile.m_friction.x >> m_defaultTile.m_friction.y;
		}
		else if (type == "ENTITY") {
			std::string name;
			keystream >> name;

			if (name == "Player" && m_playerId != -1) continue;

			int entityId = m_context->m_entityManager->AddEntity(name);
			if (entityId < 0) continue;

			if (name == "Player") {
				m_playerId = entityId;
			}

			C_Base* position = m_context->m_entityManager->GetComponent<C_Position>(entityId, Component::Position);
			if (position) {
				keystream >> *position;
			}
		}
		else {
			std::cout << "! Unknown type \"" << type << "\"." << std::endl;
		}
	}

	mapFile.close();
	std::cout << "--- Map Loaded! ---" << std::endl;
}

void Map::Update(float dt) {}

void Map::Draw(unsigned int layer) {
	if (layer >= Sheet::Num_Layers) return;

	sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
	sf::FloatRect viewSpace = m_context->m_window->GetViewSpace();

	sf::Vector2i tileBegin(static_cast<int>(floor(viewSpace.left / Sheet::Tile_Size)), 
		static_cast<int>(floor(viewSpace.top / Sheet::Tile_Size)));
	sf::Vector2i tileEnd(static_cast<int>(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size)),
		static_cast<int>(ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size)));

	unsigned int count = 0;

	// Any way to batch this before the final draw???
	for (int x = tileBegin.x; x <= tileEnd.x; ++x) {
		for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
			Tile* tile = GetTile(x, y, layer);
			if (!tile) continue;

			sf::Sprite& sprite = tile->m_properties->m_sprite;
			sprite.setPosition(static_cast<float>(x * Sheet::Tile_Size), static_cast<float>(y * Sheet::Tile_Size));
			window->draw(sprite);
			++count;
		}
	}
}

unsigned int Map::ConvertCoords(unsigned int x, unsigned int y, unsigned int layer) const {
	return (layer * m_maxMapSize.y + y) * m_maxMapSize.x + x;
}

void Map::LoadTiles(const std::string & path) {
	std::ifstream tileSetFile;
	tileSetFile.open(Utils::GetWorkingDirectory() + path);
	if (!tileSetFile.is_open()) {
		std::cout << "! Failed loading tile set file: " << path << std::endl;
		return;
	}

	std::string line;
	while (std::getline(tileSetFile, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);

		int tileId;
		keystream >> tileId;

		if (tileId < 0) continue;

		TileInfo* tile = new TileInfo(m_context, "TileSheet", tileId);
		keystream >> tile->m_name >> tile->m_friction.x >> tile->m_friction.y >> tile->m_deadly;

		if (!m_tileSet.emplace(tileId, tile).second) {
			std::cout << "! Duplicate tile type: " << tile->m_name << std::endl;
			delete tile;
			tile = nullptr;
		}
	}

	tileSetFile.close();
}

void Map::PurgeMap() {
	while (m_tileMap.begin() != m_tileMap.end()) {
		delete m_tileMap.begin()->second;
		m_tileMap.erase(m_tileMap.begin());
	}

	m_tileCount = 0;
	m_context->m_entityManager->Purge();
}

void Map::PurgeTileSet() {
	while (m_tileSet.begin() != m_tileSet.end()) {
		delete m_tileSet.begin()->second;
		m_tileSet.erase(m_tileSet.begin());
	}

	m_tileSetCount = 0;
}