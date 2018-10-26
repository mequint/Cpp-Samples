#pragma once

#include "BaseState.h"

class State_Title : public BaseState
{
	public:
		State_Title(StateManager* stateManager);
		~State_Title();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();
};