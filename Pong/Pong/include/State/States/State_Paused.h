#pragma once

#include "qe/Event/EventManager.h"
#include "qe/State/BaseState.h"

class State_Paused : public qe::BaseState
{
	public:
		State_Paused(qe::StateManager* stateManager);
		~State_Paused();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();

		void Unpause(qe::EventDetails* details);

	private:
		sf::Text m_text;
		sf::RectangleShape m_rect;

		float m_timePassed;
		bool m_hidden;
};