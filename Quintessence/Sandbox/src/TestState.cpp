#include "TestState.h"

#include <iostream>

#include "qe/Context.h"
#include "qe/ECS/SystemManager.h"
#include "qe/State/StateManager.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/Window/Window.h"

#include "ECS/ECSTypes.h"
#include "ECS/Components//Components.h"

TestState::TestState(qe::StateManager * stateManager) :
	BaseState(stateManager) {
}

void TestState::onCreate() {
	std::cout << "Creating TestState" << std::endl;

	// Setup texture
	auto textures = m_stateManager->getContext()->m_textureManager;
	auto texture = textures->getResource("PacMan");
	//m_sprite.setTexture(*texture);
	//m_sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);

	// Setup text
	auto fonts = m_stateManager->getContext()->m_fontManager;
	m_text.setFont(*fonts->getResource("Game"));
	m_text.setCharacterSize(18);
	m_text.setString("Pac Man");
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.0f, m_text.getGlobalBounds().height / 2.0f);
	m_text.setPosition(400.0f, 300.0f + texture->getSize().y);

	// Setup entity
	auto entityManager = m_stateManager->getContext()->m_entityManager;

	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::Position));
	bits.set(static_cast<qe::ComponentType>(Component::Sprite));
	
	int id = entityManager->addEntity(bits);

	auto position = entityManager->getComponent<C_Position>(id, static_cast<qe::ComponentType>(Component::Position));
	position->setPosition(400.0f, 300.0f);

	auto sprite = entityManager->getComponent<C_Sprite>(id, static_cast<qe::ComponentType>(Component::Sprite));
	sprite->create(textures, "PacMan");

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
	m_stateManager->getContext()->m_systemManager->update(time.asSeconds());
}

void TestState::draw() {
	m_stateManager->getContext()->m_systemManager->draw(m_stateManager->getContext()->m_window);
	//renderer->draw(m_sprite);

	// GUI Rendering
	auto renderer = m_stateManager->getContext()->m_window->getRenderWindow();
	renderer->draw(m_text);
}

void TestState::onClose(qe::EventDetails * details) {
	m_stateManager->getContext()->m_window->close(details);
}

void TestState::onClick(qe::EventDetails * details) {
	std::cout << details->m_mouse.x << " " << details->m_mouse.y << std::endl;
}