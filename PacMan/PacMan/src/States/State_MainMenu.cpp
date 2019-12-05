#include "States/State_MainMenu.h"

#include "qe/Context.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

State_MainMenu::State_MainMenu(qe::StateManager * stateManager) :
	BaseState(stateManager) {
}

void State_MainMenu::onCreate() {
	auto events = m_stateManager->getContext()->m_eventManager;
	events->addCallback(qe::StateType::MainMenu, "KeyDown_Escape", &State_MainMenu::onClose, this);
}

void State_MainMenu::onDestroy() {
	auto events = m_stateManager->getContext()->m_eventManager;
	events->removeCallback(qe::StateType::MainMenu, "KeyDown_Escape");
}

void State_MainMenu::onEnter() {
}

void State_MainMenu::onExit() {
}

void State_MainMenu::update(const sf::Time & time) {
}

void State_MainMenu::draw() {
}

void State_MainMenu::onClose(qe::EventDetails * details) {
	m_stateManager->getContext()->m_window->close(details);
}