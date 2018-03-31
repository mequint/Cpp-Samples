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

		virtual void GetInput();
		virtual void Update();
		virtual void Display();

	private:
		bool m_promptEnabled;
		MainMenuCommands m_menuChoice;

		bool m_messageDisplayed;
};