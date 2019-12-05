#pragma once

#include "qe/State/BaseState.h"

class State_Game : public qe::BaseState {
public:
	State_Game(qe::StateManager* stateManager);

	// Inherited via BaseState
	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onEnter() override;

	virtual void onExit() override;

	virtual void update(const sf::Time & time) override;

	virtual void draw() override;
};