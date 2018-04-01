#pragma once

#include "GameState.h"

class DisplayRulesGameState : public GameState
{
	public:
		DisplayRulesGameState(StateManager* stateManager);

		virtual void Run();
};