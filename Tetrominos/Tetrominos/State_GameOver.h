#pragma once

#include "BaseState.h"

class State_GameOver : public BaseState
{
	public:
		State_GameOver(StateManager* stateManager);
		~State_GameOver();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();
};