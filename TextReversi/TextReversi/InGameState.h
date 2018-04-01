#pragma once

#include "GameState.h"

class InGameState : public GameState
{
	public:
		InGameState(StateManager* stateManager);

		virtual void Run();
};