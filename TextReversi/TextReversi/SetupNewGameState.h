#pragma once

#include "GameState.h"

class SetupNewGameState : public GameState
{
	public:
		SetupNewGameState(StateManager* stateManager);

		virtual void Run();
};