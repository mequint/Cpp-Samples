#include "Game.h"

#include "State_Game.h"

Game::Game() : m_window("Tetrominos", sf::Vector2u(800, 600)), m_stateManager(&m_context)
{
	// Start the clock
	m_clock.restart();

	// Setup context
	m_context.m_window = &m_window;
	
	m_stateManager.ChangeState(StateType::Game);
}

Game::~Game() {}

void Game::Update()
{
	m_stateManager.HandleEvents();

	m_window.Update();
	m_stateManager.Update(m_elapsedTime);
}

void Game::Draw()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::PostProcess()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

sf::Time Game::GetElapsedtime()
{
	return m_clock.getElapsedTime();
}

Window* Game::GetWindow()
{
	return &m_window;
}

/**************************************** Helper methods ****************************************/

void Game::RestartClock()
{
	m_elapsedTime = m_clock.restart();
}