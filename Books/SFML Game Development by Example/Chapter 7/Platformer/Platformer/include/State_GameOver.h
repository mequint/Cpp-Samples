#pragma once

#include "BaseState.h"

class State_GameOver : public BaseState {
public:
	State_GameOver(StateManager* stateManager) : BaseState(stateManager) {}
	~State_GameOver() {}

	void OnCreate() {}
	void OnDestroy() {}

	void Activate() {}
	void Deactivate() {}

	void Update(const sf::Time& time) {}
	void Draw() {}
};