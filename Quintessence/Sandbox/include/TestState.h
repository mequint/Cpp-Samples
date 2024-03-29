#pragma once

#include <SFML/Graphics.hpp>

#include "qe/Animation/SpriteAnimation.h"
#include "qe/State/BaseState.h"
#include "qe/Window/EventManager.h"

class TestState : public qe::BaseState{
public:
	TestState(qe::StateManager* stateManager);

	// Inherited via BaseState
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

	// Callbacks
	void onNextScreen(qe::EventDetails* details);
	void onClose(qe::EventDetails* details);
	void onClick(qe::EventDetails* details);

private:
	sf::Text m_text;
	sf::Sprite m_sprite;
	std::unique_ptr<qe::SpriteAnimation> m_animation;
};