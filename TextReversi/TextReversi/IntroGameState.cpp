#include "IntroGameState.h"

#include <iostream>

#include "StateManager.h"

IntroGameState::IntroGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_messageDisplayed(false)
{}

void IntroGameState::GetInput() {}
void IntroGameState::Update() 
{
	if (m_messageDisplayed)
	{
		m_stateManager->ChangeState(GameStateType::MainMenu);
	}
	m_messageDisplayed = true;
}

void IntroGameState::Display()
{
	std::cout << "!!! TextReversi !!!\n\n";
}