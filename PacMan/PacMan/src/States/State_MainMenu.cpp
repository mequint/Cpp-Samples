#include "States/State_MainMenu.h"

#include "qe/Context.h"
#include "qe/Resource/FontManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

State_MainMenu::State_MainMenu(qe::StateManager * stateManager) :
	BaseState(stateManager),
	m_animateText(false),
	m_animatedTextTime(0.0f),
	m_fadingOut(false),
	m_fadeOutTime(0.0f) {
}

void State_MainMenu::onCreate() {
	auto fontManager = m_stateManager->getContext()->m_fontManager;

	auto font = fontManager->getResource("Game");

	// Setup Title label
	m_titleText.setFont(*font);
	m_titleText.setString("PAC MAN");
	m_titleText.setCharacterSize(156);
	m_titleText.setStyle(sf::Text::Bold);
	m_titleText.setFillColor(sf::Color::Yellow);
	m_titleText.setOrigin(m_titleText.getGlobalBounds().width / 2.0f, 0.0f);
	m_titleText.setPosition(400.0f, 100.0f);

	// Setup Start Game label
	m_startGameText.setFont(*font);
	m_startGameText.setString("Press Enter");
	m_startGameText.setCharacterSize(18);
	m_startGameText.setStyle(sf::Text::Bold);
	m_startGameText.setFillColor(sf::Color::White);
	m_startGameText.setOrigin(m_startGameText.getGlobalBounds().width / 2.0f, 0.0f);
	m_startGameText.setPosition(400.0f, 350.0f);

	// Setup Copyright Information label
	m_copyrightInformation.setFont(*font);
	m_copyrightInformation.setString("This clone is for learning purposes and should never be sold.");
	m_copyrightInformation.setCharacterSize(18);
	m_copyrightInformation.setFillColor(sf::Color::White);
	m_copyrightInformation.setOrigin(m_copyrightInformation.getGlobalBounds().width / 2.0f, 0.0f);
	m_copyrightInformation.setPosition(400.0f, 500.0f);

	// Setup Fade Overlay
	m_overlay.setSize(sf::Vector2f(800.0f, 600.0f));
	m_overlay.setFillColor(sf::Color(0, 0, 0, 0));

	// Setup event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->addCallback(qe::StateType::MainMenu, "KeyDown_Escape", &State_MainMenu::onClose, this);
	events->addCallback(qe::StateType::MainMenu, "KeyDown_Enter", &State_MainMenu::onStartGame, this);
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
	if (m_animateText && !m_fadingOut) {
		m_animatedTextTime += time.asSeconds();

		if (m_animatedTextTime >=  0.5f) {
			m_animateText = false;
			m_fadingOut = true;
		}
	}

 	if (m_fadingOut) {
		m_fadeOutTime += time.asSeconds();

		auto overlayColor = m_overlay.getFillColor();
		overlayColor.a = 255 * (m_fadeOutTime / 0.5f);
		m_overlay.setFillColor(overlayColor);

		if (m_fadeOutTime >= 0.5f) {
			m_stateManager->changeState(qe::StateType::Game);
		}
	}
}

void State_MainMenu::draw() {
	auto renderer = m_stateManager->getContext()->m_window->getRenderWindow();

	renderer->draw(m_titleText);
	if (!(m_animatedTextTime >= 1.0f / 12.0f && m_animatedTextTime <= 2.0f / 12.0f) && 
		!(m_animatedTextTime >= 3.0f / 12.0f && m_animatedTextTime <= 4.0f / 12.0f) &&
		!(m_animatedTextTime >= 5.0f / 12.0f && m_animatedTextTime <= 0.5f)) {
		renderer->draw(m_startGameText);
	}

	renderer->draw(m_copyrightInformation);

	renderer->draw(m_overlay);
}

void State_MainMenu::onClose(qe::EventDetails * details) {
	m_stateManager->getContext()->m_window->close(details);
}

void State_MainMenu::onStartGame(qe::EventDetails * details) {
	m_animateText = true;
	//m_fadingOut = true;
	// m_animatingText = true;
	//m_stateManager->changeState(qe::StateType::Game);
	// 1. Animate the start text
	// 2. Fade out
}