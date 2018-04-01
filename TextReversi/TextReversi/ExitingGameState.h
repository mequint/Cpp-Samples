#pragma once

#include "GameState.h"

class ExitingGameState : public GameState
{
	public:
		ExitingGameState(StateManager* stateManager);

		virtual void Run();
};