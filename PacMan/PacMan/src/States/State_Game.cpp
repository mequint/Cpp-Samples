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

	if (!m_tileMapManager.loadMap("GameMap", "../media/Maps/PacManMap.json")) {
		std::cout << "Could not load PacManMap.json" << std::endl;
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

	_setupScoreEntity();
	_setupPacmanEntity();
	_setupPowerPillEntities();
	_setupPelletEntities();

	//auto textureManager = m_stateManager->getContext()->m_textureManager;
	//m_pacmanTexture = *textureManager->getResource("PacMan");
	//m_liveSprite.setTexture(m_pacmanTexture);

	//m_readyLabel.setFont(*fontManager->getResource("Game"));
	//m_readyLabel.setCharacterSize(20);
	//m_readyLabel.setString("READY!");
	//m_readyLabel.setStyle(sf::Text::Bold);
	//m_readyLabel.setOrigin(m_readyLabel.getGlobalBounds().width / 2.0f, 0.0f);
	//m_readyLabel.setPosition(windowSize.x / 2.0f, 320.0f);
	//m_readyLabel.setFillColor(sf::Color::Yellow);

	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Game, "Escape_KeyDown", &State_Game::onQuit, this);
	eventManager->addCallback(StateType::Game, "P_KeyDown", &State_Game::onPause, this);

	eventManager->addCallback(StateType::Game, "W_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "A_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "S_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "D_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "Up_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "Down_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "Left_KeyDown", &State_Game::onMove, this);
	eventManager->addCallback(StateType::Game, "Right_KeyDown", &State_Game::onMove, this);
}

void State_Game::onDestroy() {
	auto eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Game, "Escape_KeyDown");
	eventManager->removeCallback(StateType::Game, "P_KeyDown");
	eventManager->removeCallback(StateType::Game, "W_KeyDown");
	eventManager->removeCallback(StateType::Game, "A_KeyDown");
	eventManager->removeCallback(StateType::Game, "S_KeyDown");
	eventManager->removeCallback(StateType::Game, "D_KeyDown");
	eventManager->removeCallback(StateType::Game, "Up_KeyDown");
	eventManager->removeCallback(StateType::Game, "Down_KeyDown");
	eventManager->removeCallback(StateType::Game, "Left_KeyDown");
	eventManager->removeCallback(StateType::Game, "Right_KeyDown");
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

	//renderer.draw(m_readyLabel);

	//for (int i = 0; i < m_lives; ++i) {
	//	m_liveSprite.setPosition(m_pacmanTexture.getSize().x / 2.0f + m_tileMapManager.getPosition().x + i * 4 + i * m_pacmanTexture.getSize().x,
	//		m_tileMapManager.getPosition().y + m_tileMapManager.getMapSize().y);
	//	m_liveSprite.setOrigin(0.0f, 0.0f);
	//	renderer.draw(m_liveSprite);
	//}
}

void State_Game::onPause(qe::EventDetails * details) {
	m_stateManager->changeState(StateType::Paused);
}

void State_Game::onQuit(qe::EventDetails * details) {
	m_stateManager->changeState(StateType::MainMenu);
}

void State_Game::onMove(qe::EventDetails * details) {
	qe::Message msg(static_cast<qe::MessageType>(EntityMessage::RequestMove));

	if (details->m_name == "W_KeyDown" || details->m_name == "Up_KeyDown") {
		msg.m_int = static_cast<int>(eDirection::Up);
	}
	else if (details->m_name == "S_KeyDown" || details->m_name == "Down_KeyDown") {
		msg.m_int = static_cast<int>(eDirection::Down);
	}
	else if (details->m_name == "A_KeyDown" || details->m_name == "Left_KeyDown") {
		msg.m_int = static_cast<int>(eDirection::Left);
	}
	else if (details->m_name == "D_KeyDown" || details->m_name == "Right_KeyDown") {
		msg.m_int = static_cast<int>(eDirection::Right);
	}

	msg.m_receiver = m_playerId;
	m_stateManager->getContext()->m_systemManager->getMessageDispatch()->dispatch(msg);
}

void State_Game::nextLevel() {
	auto entityManager = m_stateManager->getContext()->m_entityManager;
	auto mapPosition = m_tileMapManager.getPosition();
	auto tileSize = m_tileMapManager.getCurrentMap().getTileSize();

	// Reset PacMan position
	auto position = entityManager->getComponent<C_Position>(m_playerId, static_cast<qe::ComponentType>(Component::Position));
	position->setPosition(mapPosition.x + tileSize * 13.5f, mapPosition.y + tileSize * 23.0f);

	auto motion = entityManager->getComponent<C_Motion>(m_playerId, static_cast<qe::ComponentType>(Component::Motion));
	motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
	motion->setDirection(eDirection::None);

	_setupPelletEntities();
	_setupPowerPillEntities();
}

void State_Game::_setupScoreEntity() {
	auto entityManager = m_stateManager->getContext()->m_entityManager;

	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::Score));

	int id = entityManager->addEntity(bits);

	auto score = entityManager->getComponent<C_Score>(id, static_cast<qe::ComponentType>(Component::Score));
	score->setScore(0);
}

void State_Game::_setupPacmanEntity() {
	auto textureManager = m_stateManager->getContext()->m_textureManager;
	auto entityManager = m_stateManager->getContext()->m_entityManager;

	auto mapPosition = m_tileMapManager.getPosition();
	auto tileSize = m_tileMapManager.getCurrentMap().getTileSize();

	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::AnimatedSprite));
	bits.set(static_cast<qe::ComponentType>(Component::Controller));
	bits.set(static_cast<qe::ComponentType>(Component::Collider));
	bits.set(static_cast<qe::ComponentType>(Component::EntityType));
	bits.set(static_cast<qe::ComponentType>(Component::Motion));
	bits.set(static_cast<qe::ComponentType>(Component::Position));
	bits.set(static_cast<qe::ComponentType>(Component::State));

	int id = entityManager->addEntity(bits);
	m_playerId = id;

	auto entityType = entityManager->getComponent<C_EntityType>(id, static_cast<qe::ComponentType>(Component::EntityType));
	entityType->setEntityType(EntityType::PacMan);

	auto position = entityManager->getComponent<C_Position>(id, static_cast<qe::ComponentType>(Component::Position));
	position->setPosition(mapPosition.x + tileSize * 13.5f, mapPosition.y + tileSize * 23.0f);

	auto motion = entityManager->getComponent<C_Motion>(id, static_cast<qe::ComponentType>(Component::Motion));
	motion->setVelocity(sf::Vector2f(0.0f, 0.0f));

	auto animatedSprite = entityManager->getComponent<C_AnimatedSprite>(id, static_cast<qe::ComponentType>(Component::AnimatedSprite));
	animatedSprite->create(textureManager, "AnimatedPacMan");
	animatedSprite->setPosition(position->getPosition());
	animatedSprite->getSprite()->changeAnimation("StopRight", true);

	auto collider = entityManager->getComponent<C_Collider>(id, static_cast<qe::ComponentType>(Component::Collider));
	collider->setAABB(sf::FloatRect(position->getPosition().x, position->getPosition().y, static_cast<float>(animatedSprite->getSize().x), static_cast<float>(animatedSprite->getSize().y)));
}

void State_Game::_setupPowerPillEntities() {
	auto textureManager = m_stateManager->getContext()->m_textureManager;
	auto entityManager = m_stateManager->getContext()->m_entityManager;

	auto mapPosition = m_tileMapManager.getPosition();
	auto tileSize = m_tileMapManager.getCurrentMap().getTileSize();

	std::vector<sf::Vector2i> pillPositions = { {1, 3}, {26,3}, {1,23}, {26,23} };
	//std::vector<sf::Vector2i> pillPositions;

	for (int i = 0; i < static_cast<int>(pillPositions.size()); ++i) {
		qe::Bitmask bits;
		bits.set(static_cast<qe::ComponentType>(Component::Collider));
		bits.set(static_cast<qe::ComponentType>(Component::Consumable));
		bits.set(static_cast<qe::ComponentType>(Component::EntityType));
		bits.set(static_cast<qe::ComponentType>(Component::Points));
		bits.set(static_cast<qe::ComponentType>(Component::Position));
		bits.set(static_cast<qe::ComponentType>(Component::Sprite));
		bits.set(static_cast<qe::ComponentType>(Component::State));

		int id = entityManager->addEntity(bits);

		auto entityType = entityManager->getComponent<C_EntityType>(id, static_cast<qe::ComponentType>(Component::EntityType));
		entityType->setEntityType(EntityType::Pill);
		
		auto position = entityManager->getComponent<C_Position>(id, static_cast<qe::ComponentType>(Component::Position));
		position->setPosition(mapPosition.x + tileSize * pillPositions[i].x, mapPosition.y + tileSize * pillPositions[i].y);

		auto sprite = entityManager->getComponent<C_Sprite>(id, static_cast<qe::ComponentType>(Component::Sprite));
		sprite->create(textureManager, "Pill");
		sprite->setPosition(position->getPosition());

		auto collider = entityManager->getComponent<C_Collider>(id, static_cast<qe::ComponentType>(Component::Collider));
		collider->setAABB(sf::FloatRect(position->getPosition().x, position->getPosition().y, static_cast<float>(sprite->getSize().x), static_cast<float>(sprite->getSize().y)));

		auto points = entityManager->getComponent<C_Points>(id, static_cast<qe::ComponentType>(Component::Points));
		points->setPoints(50);
	}
}

void State_Game::_setupPelletEntities() {
	auto textureManager = m_stateManager->getContext()->m_textureManager;
	auto entityManager = m_stateManager->getContext()->m_entityManager;

	auto mapPosition = m_tileMapManager.getPosition();
	auto tileSize = m_tileMapManager.getCurrentMap().getTileSize();

	std::vector<sf::Vector2i> pelletPositions = {
		{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1},{9,1},{10,1},{11,1},{12,1},{15,1},{16,1},{17,1},{18,1},{19,1},{20,1},{21,1},{22,1},{23,1},{24,1},{25,1},{26,1},
		{1,2},{6,2},{12,2},{15,2},{21,2},{26,2},
		{6,3},{12,3},{15,3},{21,3},
		{1,4},{6,4},{12,4},{15,4},{21,4},{26,4},
		{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5},{8,5},{9,5},{10,5},{11,5},{12,5},{13,5},{14,5},{15,5},{16,5},{17,5},{18,5},{19,5},{20,5},{21,5},{22,5},{23,5},{24,5},{25,5},{26,5},
		{1,6},{6,6},{9,6},{18,6},{21,6},{26,6},
		{1,7},{6,7},{9,7},{18,7},{21,7},{26,7},
		{1,8},{2,8},{3,8},{4,8},{5,8},{6,8},{9,8},{10,8},{11,8},{12,8},{15,8},{16,8},{17,8},{18,8},{21,8},{22,8},{23,8},{24,8},{25,8},{26,8},
		{6,9},{12,9},{15,9},{21,9},
		{6,10},{12,10},{15,10},{21,10},
		{6,11},{21,11},
		{6,12},{21,12},
		{6,13},{21,13},
		{6,14},{21,14},
		{6,15},{21,15},
		{6,16},{21,16},
		{6,17},{21,17},
		{6,18},{21,18},
		{6,19},{21,19},
		{1,20},{2,20},{3,20},{4,20},{5,20},{6,20},{7,20},{8,20},{9,20},{10,20},{11,20},{12,20},{15,20},{16,20},{17,20},{18,20},{19,20},{20,20},{21,20},{22,20},{23,20},{24,20},{25,20},{26,20},
		{1,21},{6,21},{12,21},{15,21},{21,21},{26,21},
		{1,22},{6,22},{12,22},{15,22},{21,22},{26,22},
		{2,23},{3,23},{6,23},{7,23},{8,23},{9,23},{10,23},{11,23},{12,23},{15,23},{16,23},{17,23},{18,23},{19,23},{20,23},{21,23},{24,23},{25,23},
		{3,24},{6,24},{9,24},{18,24},{21,24},{24,24},
		{3,25},{6,25},{9,25},{18,25},{21,25},{24,25},
		{1,26},{2,26},{3,26},{4,26},{5,26},{6,26},{9,26},{10,26},{11,26},{12,26},{15,26},{16,26},{17,26},{18,26},{21,26},{22,26},{23,26},{24,26},{25,26},{26,26},
		{1,27},{12,27},{15,27},{26,27},
		{1,28},{12,28},{15,28},{26,28},
		{1,29},{2,29},{3,29},{4,29},{5,29},{6,29},{7,29},{8,29},{9,29},{10,29},{11,29},{12,29},{13,29},{14,29},{15,29},{16,29},{17,29},{18,29},{19,29},{20,29},{21,29},{22,29},{23,29},{24,29},{25,29},{26,29}
	};
	
	//std::vector<sf::Vector2i> pelletPositions = { {6,23},{7,23},{8,23},{9,23},{10,23},{11,23},{12,23},{15,23},{16,23},{17,23},{18,23},{19,23},{20,23},{21,23} };

	for (int i = 0; i < static_cast<int>(pelletPositions.size()); ++i) {
		qe::Bitmask bits;
		bits.set(static_cast<qe::ComponentType>(Component::Collider));
		bits.set(static_cast<qe::ComponentType>(Component::Consumable));
		bits.set(static_cast<qe::ComponentType>(Component::EntityType));
		bits.set(static_cast<qe::ComponentType>(Component::Position));
		bits.set(static_cast<qe::ComponentType>(Component::Points));
		bits.set(static_cast<qe::ComponentType>(Component::Sprite));
		bits.set(static_cast<qe::ComponentType>(Component::State));

		int id = entityManager->addEntity(bits);

		auto entityType = entityManager->getComponent<C_EntityType>(id, static_cast<qe::ComponentType>(Component::EntityType));
		entityType->setEntityType(EntityType::Dot);

		auto position = entityManager->getComponent<C_Position>(id, static_cast<qe::ComponentType>(Component::Position));
		position->setPosition(mapPosition.x + tileSize * pelletPositions[i].x, mapPosition.y + tileSize * pelletPositions[i].y);

		auto sprite = entityManager->getComponent<C_Sprite>(id, static_cast<qe::ComponentType>(Component::Sprite));
		sprite->create(textureManager, "Pellet");
		sprite->setPosition(position->getPosition());

		auto collider = entityManager->getComponent<C_Collider>(id, static_cast<qe::ComponentType>(Component::Collider));
		collider->setAABB(sf::FloatRect(position->getPosition().x, position->getPosition().y, static_cast<float>(sprite->getSize().x), static_cast<float>(sprite->getSize().y)));

		auto points = entityManager->getComponent<C_Points>(id, static_cast<qe::ComponentType>(Component::Points));
		points->setPoints(10);
	}
}