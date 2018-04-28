#pragma once

#include "State.h"

class CreditsState : public State
{
	public:
		CreditsState(StateManager* stateManager);
		virtual ~CreditsState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update();
		virtual void Draw();
};