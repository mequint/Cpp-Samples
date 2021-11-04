#include "Tile/TileMapManager.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#include "qe/Utilities/Utilities.h"

TileMapManager::TileMapManager(qe::TextureManager * textureManager) : 
	m_textureManager(textureManager) {}

bool TileMapManager::loadMap(const std::string& name, const std::string & path) {
	auto map = std::make_unique<TileMap>();

	if (!map->loadFromJsonFile(qe::Utils::getWorkingDirectory() + path)) {
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
	int tileSize = m_currentMap.getTileSize();

	// Debug tile
	//sf::RectangleShape rect;
	//rect.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
	//rect.setOutlineColor(sf::Color(255, 255, 255, 64));
	//rect.setOutlineThickness(1.0f);
	//rect.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < m_currentMap.getHeight(); ++i) {
		for (int j = 0; j < m_currentMap.getWidth(); ++j) {
			int tile = m_currentMap.getMapTile(j, i);

			int x = tile % m_tileColumns;
			int y = tile / m_tileColumns;

			m_tileSprite.setPosition(m_position.x + static_cast<float>(j * tileSize), m_position.y + static_cast<float>(i * tileSize));
			m_tileSprite.setTextureRect(sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
			
			renderer.draw(m_tileSprite);

			//rect.setPosition(m_position.x + static_cast<float>(j * tileSize), m_position.y + static_cast<float>(i * tileSize));
			
			// Draw debug tile
			//renderer.draw(rect);
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

Tile TileMapManager::getTileData(int tileX, int tileY, const eDirection& direction) const {
	switch (direction) {
	case eDirection::Up: return m_currentMap.getTileData(m_currentMap.getMapTile(tileX, tileY - 1));
	case eDirection::Down: return m_currentMap.getTileData(m_currentMap.getMapTile(tileX, tileY + 1));
	case eDirection::Left: return m_currentMap.getTileData(m_currentMap.getMapTile(tileX - 1, tileY));
	case eDirection::Right: return m_currentMap.getTileData(m_currentMap.getMapTile(tileX + 1, tileY));
	}

	return m_currentMap.getTileData(m_currentMap.getMapTile(tileX, tileY));
}

sf::Vector2i TileMapManager::getTileIndex(const sf::Vector2f& entityPosition)
{
	int tileX = static_cast<int>(entityPosition.x - m_position.x) / m_currentMap.getTileSize();
	int tileY = static_cast<int>(entityPosition.y - m_position.y) / m_currentMap.getTileSize();

	return sf::Vector2i(tileX, tileY);
}

sf::Vector2f TileMapManager::getTilePosition(int tileX, int tileY, const eDirection& direction) {
	auto tileSize = m_currentMap.getTileSize();

	switch (direction) {
		case eDirection::Up: return m_position + sf::Vector2f(static_cast<float>(tileX * tileSize), static_cast<float>((tileY - 1) * tileSize));
		case eDirection::Down: return m_position + sf::Vector2f(static_cast<float>(tileX * tileSize), static_cast<float>((tileY + 1) * tileSize));
		case eDirection::Left: return m_position + sf::Vector2f(static_cast<float>((tileX - 1) * tileSize), static_cast<float>(tileY * tileSize));
		case eDirection::Right: return m_position + sf::Vector2f(static_cast<float>((tileX + 1) * tileSize), static_cast<float>(tileY * tileSize));
	}

	return m_position + sf::Vector2f(static_cast<float>(tileX * tileSize), static_cast<float>(tileY * tileSize));
}