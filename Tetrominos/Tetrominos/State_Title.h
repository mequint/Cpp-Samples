#pragma once

#include "BaseState.h"
#include "EventManager.h"

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

		void Continue(EventDetails* details);
		void Credits(EventDetails* details);

	private:
		sf::Font m_font;
		sf::Text m_titleText;
		sf::Text m_subTitle;
};