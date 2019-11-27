#pragma once

#include "BaseState.h"
#include "EventManager.h"

class State_Paused : public BaseState {
public:
	State_Paused(StateManager* stateManager);
	~State_Paused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void Unpause(EventDetails* details);

private:
	sf::Text m_text;
	sf::RectangleShape m_rect;
};