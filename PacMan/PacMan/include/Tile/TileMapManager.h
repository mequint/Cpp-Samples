#pragma once

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

#include "qe/Resource/TextureManager.h"

#include "TileMap.h"

using MapContainer = std::unordered_map<std::string, std::unique_ptr<TileMap>>;

class TileMapManager {
public:
	TileMapManager(qe::TextureManager* textureManager);

	bool loadMap(const std::string& name, const std::string& path);

	void update(float dt);
	void draw(sf::RenderTarget& renderer);

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);

	const TileMap& getCurrentMap() const;
	sf::Vector2f getMapSize() const;

private:
	MapContainer m_maps;
	TileMap m_currentMap;

	qe::TextureManager* m_textureManager;

	unsigned int m_tileRows;
	unsigned int m_tileColumns;

	sf::Vector2f m_position;
	sf::Sprite m_tileSprite;
};