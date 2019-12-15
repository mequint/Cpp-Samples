#include "States/State_Game.h"

#include <iostream>

#include "qe/Context.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

#include "States/StateTypes.h"

State_Game::State_Game(qe::StateManager * stateManager) :
	BaseState(stateManager),
	m_tileMapManager(m_stateManager->getContext()->m_textureManager) {

	m_lives = 5;

	if (!m_tileMapManager.loadMap("GameMap", "../media/Maps/PacMan.map")) {
		std::cout << "Could not load PacMan.map" << std::endl;
		return;
	}

	// Center the map
	auto windowSize = static_cast<sf::Vector2f>(m_stateManager->getContext()->m_window->getRenderWindow()->getSize());
	auto center = sf::Vector2f(windowSize.x / 2.0f - m_tileMapManager.getMapSize().x / 2.0f,
		windowSize.y / 2.0f - m_tileMapManager.getMapSize().y / 2.0f);
	m_tileMapManager.setPosition(center);
}

void State_Game::onCreate() {
	auto windowSize = static_cast<sf::Vector2f>(m_stateManager->getContext()->m_window->getRenderWindow()->getSize());

	auto textureManager = m_stateManager->getContext()->m_textureManager;
	m_pacmanTexture = *textureManager->getResource("PacMan");

	m_pacmanSprite.setTexture(m_pacmanTexture);
	m_pacmanSprite.setOrigin(static_cast<sf::Vector2f>(m_pacmanTexture.getSize()) / 2.0f);
	m_pacmanSprite.setPosition(400.0f, 428.0f);

	m_liveSprite.setTexture(m_pacmanTexture);

	auto fontManager = m_stateManager->getContext()->m_fontManager;
	m_scoreLabel.setFont(*fontManager->getResource("Game"));
	m_scoreLabel.setCharacterSize(16);
	m_scoreLabel.setString("SCORE");
	m_scoreLabel.setStyle(sf::Text::Bold);
	m_scoreLabel.setOrigin(m_scoreLabel.getGlobalBounds().width / 2.0f, 0.0f);
	m_scoreLabel.setPosition(windowSize.x / 2.0f, 14.0f);

	m_score.setFont(*fontManager->getResource("Game"));
	m_score.setCharacterSize(16);
	m_score.setString("0");
	m_score.setStyle(sf::Text::Bold);
	m_score.setOrigin(m_score.getGlobalBounds().width / 2.0f, 0.0f);
	m_score.setPosition(windowSize.x / 2.0f, 32.0f);

	m_readyLabel.setFont(*fontManager->getResource("Game"));
	m_readyLabel.setCharacterSize(20);
	m_readyLabel.setString("READY!");
	m_readyLabel.setStyle(sf::Text::Bold);
	m_readyLabel.setOrigin(m_readyLabel.getGlobalBounds().width / 2.0f, 0.0f);
	m_readyLabel.setPosition(windowSize.x / 2.0f, 320.0f);
	m_readyLabel.setFillColor(sf::Color::Yellow);

	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Escape", &State_Game::onQuit, this);
	// TODO: P for Pause
	// TODO: Up-Down-Left-Right, WASD for Move
}

void State_Game::onDestroy() {
	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Escape");
}

void State_Game::onEnter() {
}

void State_Game::onExit() {
}

void State_Game::update(const sf::Time & time) {
	m_tileMapManager.update(time.asSeconds());
}

void State_Game::draw() {
	auto& renderer = *m_stateManager->getContext()->m_window->getRenderWindow();
	m_tileMapManager.draw(renderer);
	
	renderer.draw(m_scoreLabel);
	renderer.draw(m_score);
	renderer.draw(m_readyLabel);

	renderer.draw(m_pacmanSprite);

	for (int i = 0; i < m_lives; ++i) {
		m_liveSprite.setPosition(m_pacmanTexture.getSize().x / 2.0f + m_tileMapManager.getPosition().x + i * 4 + i * m_pacmanTexture.getSize().x,
			m_tileMapManager.getPosition().y + m_tileMapManager.getMapSize().y);
		m_liveSprite.setOrigin(0.0f, 0.0f);
		renderer.draw(m_liveSprite);
	}
}

void State_Game::onPause(qe::EventDetails * details) {
	//m_stateManager->changeState(qe::StateType::Pause);
}

void State_Game::onQuit(qe::EventDetails * details) {
	m_stateManager->changeState(static_cast<qe::StateType>(StateType::MainMenu));
}

void State_Game::onMove(qe::EventDetails * details) {
}