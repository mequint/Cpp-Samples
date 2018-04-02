#include "LoadGameState.h"

#include <iostream>
#include <string>

#include "Input.h"
#include "StateManager.h"

LoadGameState::LoadGameState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void LoadGameState::Run()
{
	std::cout << "\nLoading game\n";
	
	std::cout << "\nEnter a game name to load: ";

	std::string filename;
	getline(std::cin, filename);

	if (!m_stateManager->GetContext()->Load(filename))
	{
		std::cout << "ERROR: Failed to load game /'" << filename << "/'";
		m_stateManager->ChangeState(GameStateType::MainMenu);
	} 

	m_stateManager->ChangeState(GameStateType::InGame);
}