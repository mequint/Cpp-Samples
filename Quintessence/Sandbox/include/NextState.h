#pragma once

#include <SFML/Graphics.hpp>

#include "qe/State/BaseState.h"
#include "qe/Window/EventManager.h"

class NextState : public qe::BaseState {
public:
	NextState(qe::StateManager* stateManager);

	// Inherited via BaseState
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

	// Callbacks
	void onClose(qe::EventDetails* details);

private:
	sf::Text m_text;
};