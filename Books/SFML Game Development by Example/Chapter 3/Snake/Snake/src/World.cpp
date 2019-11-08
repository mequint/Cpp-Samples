#include "World.h"

World::World(const sf::Vector2u& windowSize) {
	m_blockSize = 16;

	m_windowSize = windowSize;

	RespawnApple();
	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(static_cast<float>(m_blockSize / 2));

	for (int i = 0; i < 4; ++i) {
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));

		if (!((i + 1) % 2)) {
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}

		if (i < 2) {
			m_bounds[i].setPosition(0.0f, 0.0f);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}

World::~World() = default;

int World::GetBlockSize() { return m_blockSize; }

void World::RespawnApple() {
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;

	m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	m_appleShape.setPosition(static_cast<float>(m_item.x * m_blockSize), static_cast<float>(m_item.y * m_blockSize));
}

void World::Update(Snake& player) {
	if (player.GetPosition() == m_item) {
		player.Extend();
		player.IncreaseScore();
		RespawnApple();
	}

	int gridSizeX = m_windowSize.x / m_blockSize;
	int gridSizeY = m_windowSize.y / m_blockSize;

	if (player.GetPosition().x <= 0 || player.GetPosition().y <= 0 ||
		player.GetPosition().x >= gridSizeX - 1 || player.GetPosition().y >= gridSizeY - 1) {
		player.Lose();
	}
}

void World::Render(sf::RenderWindow & window) {
	for (int i = 0; i < 4; ++i) {
		window.draw(m_bounds[i]);
	}

	window.draw(m_appleShape);
}