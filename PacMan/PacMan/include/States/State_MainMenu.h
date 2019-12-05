#pragma once

#include "qe/State/BaseState.h"
#include "qe/Window/EventDetails.h"

class State_MainMenu : public qe::BaseState {
public:
	State_MainMenu(qe::StateManager* stateManager);

	// Inherited via BaseState
	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onEnter() override;

	virtual void onExit() override;

	virtual void update(const sf::Time & time) override;

	virtual void draw() override;

	void onClose(qe::EventDetails* details);
};