#include "GameOverState.h"

#include <iostream>

#include "StateManager.h"

GameOverState::GameOverState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void GameOverState::Run()
{
	std::cout << "The game has concluded - let's go back to the main menu";

	m_stateManager->GetContext()->Reset();
	m_stateManager->ChangeState(GameStateType::MainMenu);

	// Display Final Score
	// Declare winner or draw

	// Ask if the player wants to play again
		// If yes
			// Reset the game
			// Change to Setup New Game state
		// If no
			// Change to Exiting game state
}