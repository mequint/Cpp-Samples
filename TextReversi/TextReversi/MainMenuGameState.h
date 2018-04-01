#pragma once

#include "GameState.h"

enum class MainMenuCommands
{
	UNSET,
	NEW_GAME,
	LOAD_GAME,
	DISPLAY_INSTRUCTIONS,
	EXIT,
	INVALID
};

class MainMenuGameState : public GameState
{
	public:
		MainMenuGameState(StateManager* stateManager);

		virtual void Run();

	private:
		MainMenuCommands m_menuChoice;

		void getMenuChoice();
};