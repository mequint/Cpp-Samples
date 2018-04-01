#include "LoadGameState.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "StateManager.h"

LoadGameState::LoadGameState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void LoadGameState::Run()
{
	std::cout << "\nLoading a saved game of Text Reversi";

	for (int i = 0; i < 3; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << ".";
	}
	std::cout << std::endl;

	m_stateManager->ChangeState(GameStateType::InGame);

	// Prompt for filename and attempt to load
	// If filename loads correctly
		// Reset the game board
		// Setup the board based on the loaded file
		// Change the state to In Game state
	// Else ask if try again
		// If yes, start over
		// If no, return to Main Menu state
}