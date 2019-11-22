#include "..\include\Game.h"

#include <iostream>

Game::Game() :
	m_window("Chapter 7", sf::Vector2u(800, 600)), 
	m_stateManager(&m_context),
	m_entityManager(&m_context, 100) {

	m_clock.restart();
	srand(static_cast<unsigned int>(std::time(nullptr)));

	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_textureManager = &m_textureManager;
	m_context.m_entityManager = &m_entityManager;

	// Debug context
	m_context.m_debugOverlay = &m_debugOverlay;
	
	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() = default;

void Game::Update() {
	m_window.Update();
	m_stateManager.Update(m_elapsed);
}

void Game::Render() {
	m_window.BeginDraw();
	m_stateManager.Draw();

	if (m_debugOverlay.Debug()) {
		m_debugOverlay.Draw(m_window.GetRenderWindow());
	}

	m_window.EndDraw();
}

void Game::LateUpdate() {
	m_stateManager.ProcessRequests();
	RestartClock();
}

sf::Time Game::GetElapsed() { return m_clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed = m_clock.restart(); }
Window* Game::GetWindow() { return &m_window; }