#pragma once

#include "GameState.h"

enum class DisplayRulesGameStateCommands
{
	UNSET,
	RETURN_HOME
};

class DisplayRulesGameState : public GameState
{
	public:
		DisplayRulesGameState();

		virtual void GetInput();
		virtual void Update();
		virtual void Display();

	private:
		bool promptEnabled;
		DisplayRulesGameStateCommands command;
};