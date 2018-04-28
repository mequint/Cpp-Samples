#pragma once

#include "State.h"

class GameOverState : public State
{
	public:
		GameOverState(StateManager* stateManager);
		virtual ~GameOverState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update();
		virtual void Draw();
};