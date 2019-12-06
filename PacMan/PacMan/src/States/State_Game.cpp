#include "States/State_Game.h"

#include <iostream>

#include "qe/Context.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

State_Game::State_Game(qe::StateManager * stateManager) :
	BaseState(stateManager),
	m_tileMapManager(m_stateManager->getContext()->m_textureManager) {

	if (!m_tileMapManager.loadMap("GameMap", "../media/Maps/PacMan.map")) {
		std::cout << "Could not load PacMan.map" << std::endl;
		return;
	}
}

void State_Game::onCreate() {
	auto textureManager = m_stateManager->getContext()->m_textureManager;
	m_tileTexture = *textureManager->getResource("GameMap");

	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(qe::StateType::Game, "KeyDown_Escape", &State_Game::onQuit, this);
	// TODO: P for Pause
	// TODO: Up-Down-Left-Right, WASD for Move
}

void State_Game::onDestroy() {
	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(qe::StateType::Game, "KeyDown_Escape");
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
}

void State_Game::onPause(qe::EventDetails * details) {
	m_stateManager->changeState(qe::StateType::Pause);
}

void State_Game::onQuit(qe::EventDetails * details) {
	m_stateManager->changeState(qe::StateType::MainMenu);
}

void State_Game::onMove(qe::EventDetails * details) {
}