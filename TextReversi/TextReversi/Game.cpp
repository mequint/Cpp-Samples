#include "Game.h"

Game::Game() : m_stateManager(&m_context)
{
	m_stateManager.ChangeState(GameStateType::Intro);
}

GameContext Game::GetContext()
{
	return m_context;
}

void Game::Run()
{
	return m_stateManager.Run();
}

bool Game::IsRunning() const
{
	return m_stateManager.IsRunning();
}