#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "qe/Window/EventDetails.h"
#include "qe/State/BaseState.h"

class State_Paused : public qe::BaseState {
public:
	State_Paused(qe::StateManager* stateManager);

	// Inherited from BaseState
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(const sf::Time & time) override;
	virtual void draw() override;

	void onResume(qe::EventDetails* details);

private:
	sf::Text m_text;
	sf::RectangleShape m_rect;

	float m_timePassed;
	bool m_hidden;
};