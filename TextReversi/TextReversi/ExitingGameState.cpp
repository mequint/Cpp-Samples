#include "ExitingGameState.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "StateManager.h"

ExitingGameState::ExitingGameState(StateManager* stateManager) :
	GameState(stateManager)
{}

void ExitingGameState::Run()
{
	std::cout << "\nProgrammed by: Michael E. Quint II\n\n";
	std::cout << "Thank you for playing! Good night!\n\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	m_stateManager->SetIsRunning(false);
}