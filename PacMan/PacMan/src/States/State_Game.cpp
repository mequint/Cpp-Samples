#include "States/State_Game.h"

#include <iostream>

#include "qe/Context.h"
#include "qe/ECS/SystemManager.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"
#include "States/StateTypes.h"
#include "Utilities/Directions.h"

State_Game::State_Game(qe::StateManager * stateManager) :
	BaseState(stateManager),
	m_tileMapManager(m_stateManager->getContext()->m_textureManager) {

	m_lives = 5;

	if (!m_tileMapManager.loadMap("GameMap", "../media/Maps/PacMan.map")) {
		std::cout << "Could not load PacMan.map" << std::endl;
		return;
	}

	// Center the map
	auto windowSize = static_cast<sf::Vector2f>(m_stateManager->getContext()->m_window->getRenderWindow()->getSize());
	auto center = sf::Vector2f(windowSize.x / 2.0f - m_tileMapManager.getMapSize().x / 2.0f,
		windowSize.y / 2.0f - m_tileMapManager.getMapSize().y / 2.0f);
	m_tileMapManager.setPosition(center);
}

void State_Game::onCreate() {
	auto windowSize = static_cast<sf::Vector2f>(m_stateManager->getContext()->m_window->getRenderWindow()->getSize());

	m_stateManager->getContext()->m_systemManager->
		getSystem<S_Movement>(static_cast<qe::SystemType>(System::Movement))->setMapManager(&m_tileMapManager);

	_setupPacmanEntity();

	auto textureManager = m_stateManager->getContext()->m_textureManager;
	m_pacmanTexture = *textureManager->getResource("PacMan");
	m_liveSprite.setTexture(m_pacmanTexture);

	auto fontManager = m_stateManager->getContext()->m_fontManager;
	m_scoreLabel.setFont(*fontManager->getResource("Game"));
	m_scoreLabel.setCharacterSize(16);
	m_scoreLabel.setString("SCORE");
	m_scoreLabel.setStyle(sf::Text::Bold);
	m_scoreLabel.setOrigin(m_scoreLabel.getGlobalBounds().width / 2.0f, 0.0f);
	m_scoreLabel.setPosition(windowSize.x / 2.0f, 14.0f);

	m_score.setFont(*fontManager->getResource("Game"));
	m_score.setCharacterSize(16);
	m_score.setString("0");
	m_score.setStyle(sf::Text::Bold);
	m_score.setOrigin(m_score.getGlobalBounds().width / 2.0f, 0.0f);
	m_score.setPosition(windowSize.x / 2.0f, 32.0f);

	m_readyLabel.setFont(*fontManager->getResource("Game"));
	m_readyLabel.setCharacterSize(20);
	m_readyLabel.setString("READY!");
	m_readyLabel.setStyle(sf::Text::Bold);
	m_readyLabel.setOrigin(m_readyLabel.getGlobalBounds().width / 2.0f, 0.0f);
	m_readyLabel.setPosition(windowSize.x / 2.0f, 320.0f);
	m_readyLabel.setFillColor(sf::Color::Yellow);

	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Escape", &State_Game::onQuit, this);
	// TODO: P for Pause

	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_W", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_A", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_S", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_D", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Up", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Down", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Left", &State_Game::onMove, this);
	eventManager->addCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Right", &State_Game::onMove, this);

}

void State_Game::onDestroy() {
	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Escape");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_W");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_A");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_S");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_D");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Up");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Down");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Left");
	eventManager->removeCallback(static_cast<qe::StateType>(StateType::Game), "KeyDown_Right");
}

void State_Game::onEnter() {
}

void State_Game::onExit() {
}

void State_Game::update(const sf::Time & time) {
	m_tileMapManager.update(time.asSeconds());
	m_stateManager->getContext()->m_systemManager->update(time.asSeconds());
}

void State_Game::draw() {
	auto& renderer = *m_stateManager->getContext()->m_window->getRenderWindow();
	m_tileMapManager.draw(renderer);

	m_stateManager->getContext()->m_systemManager->draw(m_stateManager->getContext()->m_window);

	renderer.draw(m_scoreLabel);
	renderer.draw(m_score);
	renderer.draw(m_readyLabel);

	renderer.draw(m_pacmanSprite);

	for (int i = 0; i < m_lives; ++i) {
		m_liveSprite.setPosition(m_pacmanTexture.getSize().x / 2.0f + m_tileMapManager.getPosition().x + i * 4 + i * m_pacmanTexture.getSize().x,
			m_tileMapManager.getPosition().y + m_tileMapManager.getMapSize().y);
		m_liveSprite.setOrigin(0.0f, 0.0f);
		renderer.draw(m_liveSprite);
	}
}

void State_Game::onPause(qe::EventDetails * details) {
	//m_stateManager->changeState(qe::StateType::Pause);
}

void State_Game::onQuit(qe::EventDetails * details) {
	m_stateManager->changeState(static_cast<qe::StateType>(StateType::MainMenu));
}

void State_Game::onMove(qe::EventDetails * details) {
	qe::Message msg(static_cast<qe::MessageType>(EntityMessage::RequestMove));

	if (details->m_name == "KeyDown_W" || details->m_name == "KeyDown_Up") {
		msg.m_int = static_cast<int>(Direction::Up);
	}
	else if (details->m_name == "KeyDown_S" || details->m_name == "KeyDown_Down") {
		msg.m_int = static_cast<int>(Direction::Down);
	}
	else if (details->m_name == "KeyDown_A" || details->m_name == "KeyDown_Left") {
		msg.m_int = static_cast<int>(Direction::Left);
	}
	else if (details->m_name == "KeyDown_D" || details->m_name == "KeyDown_Right") {
		msg.m_int = static_cast<int>(Direction::Right);
	}

	msg.m_receiver = m_playerId;
	m_stateManager->getContext()->m_systemManager->getMessageDispatch()->dispatch(msg);
}

void State_Game::_setupPacmanEntity() {
	auto textureManager = m_stateManager->getContext()->m_textureManager;
	auto entityManager = m_stateManager->getContext()->m_entityManager;

	auto mapPosition = m_tileMapManager.getPosition();
	auto tileSize = m_tileMapManager.getCurrentMap().getTileSize();

	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::Controller));
	bits.set(static_cast<qe::ComponentType>(Component::Motion));
	bits.set(static_cast<qe::ComponentType>(Component::Position));
	bits.set(static_cast<qe::ComponentType>(Component::Sprite));
	bits.set(static_cast<qe::ComponentType>(Component::State));

	int id = entityManager->addEntity(bits);
	m_playerId = id;

	auto position = entityManager->getComponent<C_Position>(id, static_cast<qe::ComponentType>(Component::Position));
	position->setPosition(mapPosition.x + tileSize * 13.5f, mapPosition.y + tileSize * 23.0f);

	auto motion = entityManager->getComponent<C_Motion>(id, static_cast<qe::ComponentType>(Component::Motion));
	motion->setVelocity(sf::Vector2f(0.0f, 0.0f));

	auto sprite = entityManager->getComponent<C_Sprite>(id, static_cast<qe::ComponentType>(Component::Sprite));
	sprite->create(textureManager, "PacMan");
	sprite->setPosition(position->getPosition());
}