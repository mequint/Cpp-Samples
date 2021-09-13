#include "NextState.h"

#include <iostream>

#include "qe/Context.h"
#include "qe/ECS/SystemManager.h"
#include "qe/State/StateManager.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/Window/Window.h"

#include "ECS/ECSTypes.h"
#include "ECS/Components//Components.h"
#include "StateTypes.h"

NextState::NextState(qe::StateManager * stateManager) :
	BaseState(stateManager) {
}

void NextState::onCreate() {
	std::cout << "Creating NextState" << std::endl;

	// Setup text
	auto fonts = m_stateManager->getContext()->m_fontManager;
	m_text.setFont(*fonts->getResource("Game"));
	m_text.setCharacterSize(18);
	m_text.setString("Press Escape to Return to Previous Screen");
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.0f, m_text.getGlobalBounds().height / 2.0f);
	m_text.setPosition(400.0f, 300.0f);

	// Add callbacks to event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->addCallback(StateType::NextState, "Escape_KeyDown", &NextState::onClose, this);
}

void NextState::onDestroy() {
	std::cout << "Destroying NextState" << std::endl;

	// Remove callbacks from event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->removeCallback(StateType::NextState, "Key_Escape_Down");
}

void NextState::onEnter() {
	std::cout << "Enter NextState" << std::endl;
}

void NextState::onExit() {
	std::cout << "Exiting NextState" << std::endl;
}

void NextState::update(const sf::Time& time) {
	m_stateManager->getContext()->m_systemManager->update(time.asSeconds());
}

void NextState::draw() {
	m_stateManager->getContext()->m_systemManager->draw(m_stateManager->getContext()->m_window);

	// GUI Rendering
	auto renderer = m_stateManager->getContext()->m_window->getRenderWindow();
	renderer->draw(m_text);
}

void NextState::onClose(qe::EventDetails * details) {
	m_stateManager->changeState(StateType::Game);
}