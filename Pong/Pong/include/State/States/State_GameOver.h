#pragma once

#include "qe/Event/EventManager.h"
#include "qe/State/BaseState.h"

class State_GameOver : public qe::BaseState {
public:
	State_GameOver(qe::StateManager* stateManager);
	~State_GameOver();

	void Create();
	void Destroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

private:
	sf::Text m_text;
	sf::RectangleShape m_rect;
};