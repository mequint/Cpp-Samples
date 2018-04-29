#pragma once

#include "State.h"

class MainMenuState : public State
{
	public:
		MainMenuState(StateManager* stateManager);
		virtual ~MainMenuState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update(float dt);
		virtual void Draw();
};