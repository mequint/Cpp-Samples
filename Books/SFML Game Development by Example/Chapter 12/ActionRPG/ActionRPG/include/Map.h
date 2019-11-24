#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "SharedContext.h"
#include "TextureManager.h"

enum Sheet { Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256, Num_Layers = 4 };

using TileID = unsigned int;

struct TileInfo {
	TileInfo(SharedContext* context, const std::string& texture = "", TileID id = 0) :
		m_context(context), m_id(0), m_deadly(false) {

		TextureManager* textureManager = context->m_textureManager;
		if (texture == "") {
			m_id = id;
			return;
		}

		if (!textureManager->RequireResource(texture)) return;

		m_texture = texture;
		m_id = id;
		m_sprite.setTexture(*textureManager->GetResource(m_texture));

		sf::IntRect tileBoundaries(m_id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
			m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
			Sheet::Tile_Size, Sheet::Tile_Size);

		m_sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo() {
		if (m_texture == "") return;
		m_context->m_textureManager->ReleaseResource(m_texture);

	}

	sf::Sprite m_sprite;

	TileID m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;

	SharedContext* m_context;
	std::string m_texture;
};

struct Tile {
	TileInfo* m_properties;
	bool m_warp;
	bool m_solid;
};

using TileMap = std::unordered_map<TileID, Tile*>;
using TileSet = std::unordered_map<TileID, TileInfo*>;

class Map {
public:
	Map(SharedContext* context);
	~Map();

	Tile* GetTile(unsigned int x, unsigned int y, unsigned int layer);
	TileInfo* GetDefaultTile();

	unsigned int GetTileSize() const;
	const sf::Vector2u& GetMapSize() const;
	const sf::Vector2f& GetPlayerStart() const;
	int GetPlayerId() const;

	void LoadMap(const std::string& path);
	
	void Update(float dt);
	void Draw(unsigned int layer);

private:
	unsigned int ConvertCoords(unsigned int x, unsigned int y, unsigned int layer) const;

	void LoadTiles(const std::string& path);
	
	void PurgeMap();
	void PurgeTileSet();

	TileSet m_tileSet;
	TileMap m_tileMap;
	TileInfo m_defaultTile;

	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	int m_playerId;

	unsigned int m_tileCount;
	unsigned int m_tileSetCount;

	SharedContext* m_context;
};