#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

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

	// Callbacks
	void onQuit(qe::EventDetails* details);
	void onPlay(qe::EventDetails* details);

private:
	sf::Text m_titleText;
	sf::Text m_startGameText;
	sf::Text m_copyrightInformation;

	bool m_animateText;
	float m_currentTime;
	float m_animatedTextTime;

	sf::RectangleShape m_overlay;
	bool m_fadingOut;
	float m_fadeOutTime;
};