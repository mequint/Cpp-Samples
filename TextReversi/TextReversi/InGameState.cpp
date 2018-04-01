#include "InGameState.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "StateManager.h"
InGameState::InGameState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void InGameState::Run()
{
	std::cout << "Playing an intense game of TextReversi";

	for (int i = 0; i < 3; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << ".";
	}
	std::cout << std::endl;

	m_stateManager->ChangeState(GameStateType::GameOver);
}