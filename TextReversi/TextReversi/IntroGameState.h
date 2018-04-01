#pragma once

#include "GameState.h"

class IntroGameState : public GameState
{
	public:
		IntroGameState(StateManager* stateManager);

		virtual void Run();
};