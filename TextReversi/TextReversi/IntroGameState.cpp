#include "IntroGameState.h"

#include <iostream>

#include "StateManager.h"

IntroGameState::IntroGameState(StateManager* stateManager) :
	GameState(stateManager)
{}

void IntroGameState::Run()
{
	std::cout << "!!! TextReversi !!!\n";

	m_stateManager->ChangeState(GameStateType::MainMenu);
}