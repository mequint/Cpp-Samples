#include "TestState.h"

#include <iostream>

#include "qe/Animation/SpriteLoader.h"
#include "qe/Context.h"
#include "qe/ECS/SystemManager.h"
#include "qe/State/StateManager.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/Utilities/Utilities.h"
#include "qe/Window/Window.h"

#include "ECS/ECSTypes.h"
#include "ECS/Components//Components.h"
#include "StateTypes.h"

TestState::TestState(qe::StateManager * stateManager) :
	BaseState(stateManager), m_animation(nullptr) {
}

void TestState::onCreate() {
	std::cout << "Creating TestState" << std::endl;

	// Setup texture
	auto textures = m_stateManager->getContext()->m_textureManager;
	auto texture = textures->getResource("PacMan");
	auto animatedTexture = textures->getResource("AnimatedPacMan");
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

	// Setup animated sprite
	qe::SpriteLoader spriteLoader(textures);
	m_animation = spriteLoader.loadFromJsonFile(qe::Utils::getWorkingDirectory() + "../media/Animations/AnimatedPacMan.json");

	// Add callbacks to event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->addCallback(StateType::Game, "Enter_KeyDown", &TestState::onNextScreen, this);
	events->addCallback(StateType::Game, "Escape_KeyDown", &TestState::onClose, this);
	events->addCallback(StateType::Game, "Left_MouseButtonDown", &TestState::onClick, this);
}

void TestState::onDestroy() {
	std::cout << "Destroying TestState" << std::endl;

	// Remove callbacks from event manager
	auto events = m_stateManager->getContext()->m_eventManager;
	events->removeCallback(StateType::Game, "Enter_KeyDown");
	events->removeCallback(StateType::Game, "Escape_KeyDown");
	events->removeCallback(StateType::Game, "Left_MouseButtonDown");
}

void TestState::onEnter() {
	std::cout << "Enter TestState" << std::endl;

	auto window = m_stateManager->getContext()->m_window;
	window->setCursor("../media/Cursors/SwordCursor.png", sf::Vector2u(0, 16));
	//window.setCursor(qe::CursorType::Text);

	m_animation->changeAnimation("MoveDown", true);
}

void TestState::onExit() {
	std::cout << "Exiting TestState" << std::endl;

	auto window = m_stateManager->getContext()->m_window;
	window->setCursor(qe::CursorType::Arrow);

	m_animation->changeAnimation("StopLeft", true);
}

void TestState::update(const sf::Time& time) {
	m_stateManager->getContext()->m_systemManager->update(time.asSeconds());
	m_animation->update(time.asSeconds());
}

void TestState::draw() {
	auto window = m_stateManager->getContext()->m_window;
	//m_stateManager->getContext()->m_systemManager->draw(window);

	// GUI Rendering
	auto renderer = window->getRenderWindow();
	renderer->draw(m_text);

	m_animation->draw(renderer);
}

void TestState::onNextScreen(qe::EventDetails* details) {
	m_stateManager->changeState(StateType::NextState);
}

void TestState::onClose(qe::EventDetails * details) {
	m_stateManager->getContext()->m_window->close(details);
}

void TestState::onClick(qe::EventDetails * details) {
	std::cout << details->m_mouse.x << " " << details->m_mouse.y << std::endl;
}