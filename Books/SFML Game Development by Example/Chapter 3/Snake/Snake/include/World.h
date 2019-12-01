#pragma once

#include "Snake.h"

class World {
public:
	World(const sf::Vector2u& windowSize);
	~World();

	int GetBlockSize();

	void RespawnApple();

	void Update(Snake& player);
	void Render(sf::RenderWindow& window);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;

	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];
};