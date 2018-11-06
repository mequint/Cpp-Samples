#pragma once

#include "BaseState.h"
#include "EventManager.h"

class State_Credits : public BaseState
{
	public:
		State_Credits(StateManager* stateManager);
		~State_Credits();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();

		void Title(EventDetails* details);

	private:
		sf::Font m_font;
		sf::Text m_labels[6];
};