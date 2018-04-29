#pragma once

#include "State.h"

class SetupNewGameState : public State
{
	public:
		SetupNewGameState(StateManager* stateManager);
		virtual ~SetupNewGameState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update(float dt);
		virtual void Draw();
};