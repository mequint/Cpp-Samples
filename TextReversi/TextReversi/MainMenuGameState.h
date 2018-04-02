#pragma once

#include "GameState.h"

enum class MainMenuCommands
{
	Unset,
	NewGame,
	LoadGame,
	DisplayInstructions,
	Exit,
	Invalid
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