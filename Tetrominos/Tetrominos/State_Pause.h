#pragma once

#include "BaseState.h"

class State_Pause : public BaseState
{
	public:
		State_Pause(StateManager* stateManager);
		~State_Pause();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void HandleEvents();
		void Update(const sf::Time& time);
		void Draw();
};