#pragma once

#include "State.h"

class PauseState : public State
{
	public:
		PauseState(StateManager* stateManager);
		virtual ~PauseState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update(float dt);
		virtual void Draw();
};