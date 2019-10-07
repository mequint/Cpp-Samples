#pragma once

#include "qe/Event/EventManager.h"
#include "qe/State/BaseState.h"

class State_Title : public qe::BaseState {
public:
	State_Title(qe::StateManager* stateManager);
	~State_Title();

	void Create();
	void Destroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void Continue(qe::EventDetails* details);

private:
	sf::Text m_titleText;
	sf::Text m_subtitleText;
};