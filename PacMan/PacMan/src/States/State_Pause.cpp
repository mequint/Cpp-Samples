#include "States/State_Paused.h"

#include "qe/Context.h"
#include "qe/Resource/FontManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

#include "States/StateTypes.h"

State_Paused::State_Paused(qe::StateManager * stateManager) : qe::BaseState(stateManager) {}

void State_Paused::onCreate() {
	setTransparent(true);

	sf::Font* font = m_stateManager->getContext()->m_fontManager->getResource("Game");
	m_text.setFont(*font);
	m_text.setString(sf::String("PAUSED"));
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0.0f, 0.0f);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	qe::EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Paused, "P_KeyDown", &State_Paused::onResume, this);
}

void State_Paused::onDestroy() {
	qe::EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Paused, "P_KeyDown");
}

void State_Paused::onEnter() {
	m_timePassed = 0.0f;
}

void State_Paused::onExit() {}

void State_Paused::update(const sf::Time & time) {
	m_timePassed += time.asSeconds();
	if (m_timePassed < 3.0f) {
		m_hidden = false;
	}
	else if (m_timePassed < 4.0f) {
		m_hidden = true;
	}
	else {
		m_hidden = false;
		m_timePassed = 0.0f;
	}
}

void State_Paused::draw() {
	sf::RenderWindow* renderer = m_stateManager->getContext()->m_window->getRenderWindow();
	renderer->draw(m_rect);

	if (!m_hidden) {
		renderer->draw(m_text);
	}
}

void State_Paused::onResume(qe::EventDetails* details) {
	m_stateManager->changeState(StateType::Game);
}