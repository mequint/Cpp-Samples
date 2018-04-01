#pragma once

#include "GameState.h"

class GameOverState : public GameState
{
	public:
		GameOverState(StateManager* stateManager);

		virtual void Run();
};