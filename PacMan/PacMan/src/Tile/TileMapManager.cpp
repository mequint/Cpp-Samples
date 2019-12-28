#include "Tile/TileMapManager.h"

#include <iostream>
#include "qe/Utilities/Utilities.h"

TileMapManager::TileMapManager(qe::TextureManager * textureManager) : 
	m_textureManager(textureManager) {}

bool TileMapManager::loadMap(const std::string& name, const std::string & path) {
	auto map = std::make_unique<TileMap>();

	if (!map->loadFromFile(qe::Utils::getWorkingDirectory() + path)) {
		std::cout << "Could not load " << name << ".map" << std::endl;
		return false;
	}

	m_maps[name] = std::move(map);

	auto texture = m_textureManager->getResource(name);
	m_tileSprite.setTexture(*texture);

	auto mapIter = m_maps.find(name);
	if (mapIter == m_maps.end()) return false;

	m_currentMap = *mapIter->second;

	m_tileColumns = texture->getSize().x / m_currentMap.getTileSize();
	m_tileRows = texture->getSize().y / m_currentMap.getTileSize();

	return true;
}

void TileMapManager::update(float dt) {
}

void TileMapManager::draw(sf::RenderTarget & renderer) {
	for (int i = 0; i < m_currentMap.getHeight(); ++i) {
		for (int j = 0; j < m_currentMap.getWidth(); ++j) {
			int tile = m_currentMap.getMapTile(j, i);

			int x = tile % m_tileColumns;
			int y = tile / m_tileColumns;

			m_tileSprite.setPosition(m_position.x + static_cast<float>(j * m_currentMap.getTileSize()), m_position.y + static_cast<float>(i * m_currentMap.getTileSize()));
			m_tileSprite.setTextureRect(sf::IntRect(x * m_currentMap.getTileSize(), y * m_currentMap.getTileSize(), m_currentMap.getTileSize(), m_currentMap.getTileSize()));
			
			renderer.draw(m_tileSprite);
		}
	}
}

const sf::Vector2f & TileMapManager::getPosition() const {
	return m_position;
}

void TileMapManager::setPosition(const sf::Vector2f & position) {
	m_position = position;
}

const TileMap& TileMapManager::getCurrentMap() const {
	return m_currentMap;
}

sf::Vector2f TileMapManager::getMapSize() const {
	auto width = static_cast<float>(m_currentMap.getTileSize() * m_currentMap.getWidth());
	auto height = static_cast<float>(m_currentMap.getTileSize() * m_currentMap.getHeight());

	return sf::Vector2f(width, height);
}
