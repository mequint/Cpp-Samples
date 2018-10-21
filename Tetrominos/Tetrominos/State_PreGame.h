#pragma once

#include "BaseState.h"

class State_PreGame : public BaseState
{
	public:
		State_PreGame(StateManager* stateManager);
		~State_PreGame();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void HandleEvents();
		void Update(const sf::Time& time);
		void Draw();
};