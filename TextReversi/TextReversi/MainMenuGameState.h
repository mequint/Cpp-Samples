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
		MainMenuGameState();

		virtual void GetInput();
		virtual void Update();
		virtual void Display();

	private:
		bool promptEnabled;
		MainMenuCommands menuChoice;

		bool displayedError;
};