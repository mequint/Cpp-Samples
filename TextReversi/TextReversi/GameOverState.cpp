#include "GameOverState.h"

GameOverState::GameOverState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void GameOverState::Run()
{
	// Display Final Score
	// Declare winner or draw

	// Ask if the player wants to play again
		// If yes
			// Reset the game
			// Change to Setup New Game state
		// If no
			// Change to Exiting game state
}