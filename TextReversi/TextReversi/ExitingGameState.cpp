#include "ExitingGameState.h"

#include <iostream>

#include "StateManager.h"

ExitingGameState::ExitingGameState(StateManager* stateManager) :
	GameState(stateManager)
{}

void ExitingGameState::Run()
{
	std::cout << "Programmed by: Michael E. Quint II\n\n";
	std::cout << "Thank you for playing! Good night!\n\n";
	m_stateManager->SetIsRunning(false);
}