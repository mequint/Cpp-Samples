#include "ExitingGameState.h"

#include <iostream>

#include "StateManager.h"

ExitingGameState::ExitingGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_messageDisplayed(false)
{}

void ExitingGameState::GetInput() {}
void ExitingGameState::Update() 
{
	if (m_messageDisplayed)
	{
		m_stateManager->SetIsRunning(false);
	}
}

void ExitingGameState::Display()
{
	std::cout << "Programmed by: Michael E. Quint II\n\n";
	std::cout << "Thank you for playing! Good night!\n\n";
	m_messageDisplayed = true;
}