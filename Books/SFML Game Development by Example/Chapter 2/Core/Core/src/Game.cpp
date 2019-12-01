#include "..\include\Game.h"

Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600)) {
	RestartClock();

	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);

	m_increment = sf::Vector2i(400, 400);
}

Game::~Game() = default;
 
void Game::HandleInput() {}

void Game::Update() {
	m_window.Update();
	MoveMushroom();
}

void Game::Render() {
	m_window.BeginDraw();
	m_window.Draw(m_mushroom);
	m_window.EndDraw();
}

Window* Game::GetWindow() {
	return &m_window;
}

sf::Time Game::GetElapsed() {
	return m_elapsed;
}

void Game::RestartClock() {
	m_elapsed = m_clock.restart();
}

void Game::MoveMushroom() {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_window.GetWindowSize());
	sf::Vector2f textSize = static_cast<sf::Vector2f>(m_mushroomTexture.getSize());

	if ((m_mushroom.getPosition().x > windowSize.x - textSize.x && m_increment.x > 0.0f) ||
		(m_mushroom.getPosition().x < 0.0f && m_increment.x < 0.0f)) {
		m_increment.x = -m_increment.x;
	}

	if ((m_mushroom.getPosition().y > windowSize.y - textSize.y && m_increment.y > 0.0f) ||
		(m_mushroom.getPosition().y < 0.0f && m_increment.y < 0.0f)) {
		m_increment.y = -m_increment.y;
	}

	float elapsed = m_elapsed.asSeconds();

	m_mushroom.setPosition(
		m_mushroom.getPosition().x + (m_increment.x * elapsed),
		m_mushroom.getPosition().y + (m_increment.y * elapsed));
}