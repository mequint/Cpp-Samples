#pragma once

#include "BaseState.h"

class State_Game : public BaseState
{
	public:
		State_Game();
		~State_Game();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void HandleEvent(sf::Event& event);
		void Update(const sf::Time& time);
		void Draw(sf::RenderWindow& window);
};