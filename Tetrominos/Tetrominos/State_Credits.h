#pragma once

#include "BaseState.h"

class State_Credits : public BaseState
{
	public:
		State_Credits(StateManager* stateManager);
		~State_Credits();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void HandleEvents();
		void Update(const sf::Time& time);
		void Draw();
};