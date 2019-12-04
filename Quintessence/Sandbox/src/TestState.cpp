#include "TestState.h"

#include <iostream>

#include "qe/Context.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

TestState::TestState(qe::StateManager * stateManager) :
	BaseState(stateManager) {
}

void TestState::onCreate() {
	std::cout << "Creating TestState" << std::endl;

	// Create resources
	if (!m_texture.loadFromFile("../media/Textures/PacMan.png")) {
		std::cout << "Could not load 'PacMan.png'" << std::endl;

		onClose(nullptr);
		return;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(400.0f, 300.0f);

	// Add callbacks to event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->addCallback(qe::StateType::Game, "Key_Escape_Down", &TestState::onClose, this);
	events->addCallback(qe::StateType::Game, "Left_Button_Down", &TestState::onClick, this);
}

void TestState::onDestroy() {
	std::cout << "Destroying TestState" << std::endl;

	// Remove callbacks from event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->removeCallback(qe::StateType::Game, "Key_Escape_Down");
	events->removeCallback(qe::StateType::Game, "Left_Button_Donw");
}

void TestState::onEnter() {
	std::cout << "Enter TestState" << std::endl;

	auto window = m_stateManager->getContext()->m_window;
	window->setCursor("../media/Cursors/SwordCursor.png", sf::Vector2u(0, 16));
	//window.setCursor(qe::CursorType::Text);
}

void TestState::onExit() {
	std::cout << "Exiting TestState" << std::endl;
}

void TestState::update(const sf::Time& time) {
}

void TestState::draw() {
	m_stateManager->getContext()->m_window->getRenderWindow()->draw(m_sprite);
}

void TestState::onClose(qe::EventDetails * details) {
	m_stateManager->getContext()->m_window->close(details);
}

void TestState::onClick(qe::EventDetails * details) {
	std::cout << details->m_mouse.x << " " << details->m_mouse.y << std::endl;
}