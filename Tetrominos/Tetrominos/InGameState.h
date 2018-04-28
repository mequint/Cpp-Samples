#pragma once

#include "State.h"

class InGameState : public State
{
	public:
		InGameState(StateManager* stateManager);
		virtual ~InGameState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update();
		virtual void Draw();
};