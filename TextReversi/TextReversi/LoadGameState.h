#pragma once

#include "GameState.h"

class LoadGameState : public GameState
{
	public:
		LoadGameState(StateManager* stateManager);

		virtual void Run();
};