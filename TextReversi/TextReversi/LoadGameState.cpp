#include "LoadGameState.h"

LoadGameState::LoadGameState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void LoadGameState::Run()
{
	// Prompt for filename and attempt to load
	// If filename loads correctly
		// Reset the game board
		// Setup the board based on the loaded file
		// Change the state to In Game state
	// Else ask if try again
		// If yes, start over
		// If no, return to Main Menu state
}