#include "..\include\Game.h"

#include <iostream>

Game::Game() : m_window("Chapter 4", sf::Vector2u(800, 600)) {
	m_clock.restart();
	srand(static_cast<unsigned int>(std::time(nullptr)));

	m_texture.loadFromFile("Mushroom.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(static_cast<sf::Vector2f>(m_texture.getSize()) / 2.0f);
	m_sprite.setPosition(0.0f, 0.0f);

	m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);
}

Game::~Game() = default;

void Game::Update() {
	m_window.Update();
}

void Game::Render() {
	m_window.BeginDraw();
	m_window.GetRenderWindow()->draw(m_sprite);
	m_window.EndDraw();
}

Window* Game::GetWindow() {
	return &m_window;
}

sf::Time Game::GetElapsed() {
	return m_clock.getElapsedTime();
}

void Game::RestartClock() {
	m_clock.restart();
}

void Game::MoveSprite(EventDetails * details) {
	sf::Vector2i mousePos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
	m_sprite.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	std::cout << "Moving sprite to: " << mousePos.x << ":" << mousePos.y << std::endl;
}