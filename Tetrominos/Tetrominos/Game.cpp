#include "Game.h"

#include "State_Game.h"

Game::Game() : m_window("Tetrominos", sf::Vector2u(800, 600)), m_currentState(nullptr)
{
	m_clock.restart();
	m_currentState = new State_Game();
	m_currentState->Activate();
}

Game::~Game() {}

void Game::Update()
{
	m_window.Update();

	m_currentState->Update(m_elapsedTime);
}

void Game::Draw()
{
	m_window.BeginDraw();

	m_window.EndDraw();
}

void Game::PostProcess()
{
	RestartClock();
}

sf::Time Game::GetElapsedtime()
{
	return m_clock.getElapsedTime();
}

Window * Game::GetWindow()
{
	return &m_window;
}

/**************************************** Helper methods ****************************************/

void Game::RestartClock()
{
	m_elapsedTime = m_clock.restart();
}
