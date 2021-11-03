#include "..\..\..\include\ECS\Systems\S_AI.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Motion.h"
#include "ECS/Components/C_Position.h"

#include "qe/ECS/SystemManager.h"

S_AI::S_AI(qe::SystemManager * systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Movement), systemManager),
	m_random(nullptr) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::GameAgent));
	req.set(static_cast<qe::ComponentType>(Component::Motion));
	m_requiredComponents.push_back(req);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::Stop), this);
}

S_AI::~S_AI() = default;

void S_AI::notify(const qe::Message & message) {
	if (std::find(m_entities.begin(), m_entities.end(), message.m_receiver) == m_entities.end()) return;

	auto entities = m_systemManager->getEntityManager();
	auto m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::Stop: {
			auto motion = entities->getComponent<C_Motion>(message.m_receiver, static_cast<qe::ComponentType>(Component::Motion));
			auto position = entities->getComponent<C_Position>(message.m_receiver, static_cast<qe::ComponentType>(Component::Position));

			auto tileSize = m_mapManager->getCurrentMap().getTileSize();
			int tileX = static_cast<int>(position->getPosition().x - m_mapManager->getPosition().x) / tileSize;
			int tileY = static_cast<int>(position->getPosition().y - m_mapManager->getPosition().y) / tileSize;

			auto physicalTile = m_mapManager->getTileData(tileX, tileY);

			auto oldDirection = motion->getDirection();

			auto newDirection = eDirection::None;
			std::vector<eDirection> potentialDirections;

			if (oldDirection == eDirection::Up || oldDirection == eDirection::Down) {
				auto potentialTile = m_mapManager->getTileData(tileX, tileY, eDirection::Left);
				if (!potentialTile.IsSolid) {
					potentialDirections.push_back(eDirection::Left);
				}

				potentialTile = m_mapManager->getTileData(tileX, tileY, eDirection::Right);
				if (!potentialTile.IsSolid) {
					potentialDirections.push_back(eDirection::Right);
				}
			}

			if (oldDirection == eDirection::Left || oldDirection == eDirection::Right) {
				auto potentialTile = m_mapManager->getTileData(tileX, tileY, eDirection::Up);
				if (!potentialTile.IsSolid) {
					potentialDirections.push_back(eDirection::Up);
				}

				potentialTile = m_mapManager->getTileData(tileX, tileY, eDirection::Down);
				if (!potentialTile.IsSolid) {
					potentialDirections.push_back(eDirection::Down);
				}
			}

			int randomDirection = m_random->nextInt(0, potentialDirections.size() - 1);

			qe::Message moveRequest(static_cast<qe::MessageType>(EntityMessage::RequestMove));
			moveRequest.m_receiver = message.m_receiver;
			moveRequest.m_int = static_cast<int>(potentialDirections[randomDirection]);
			m_systemManager->getMessageDispatch()->dispatch(moveRequest);
			break;
		}
	}
}

void S_AI::update(float dt) {
	auto entityManager = m_systemManager->getEntityManager();

	// 1. For all AI entities
	for (auto& entity : m_entities) {
	}
}

void S_AI::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
	// Events in this case will be game state changes such as scramble, chase, and runaway
}

void S_AI::setRandomGenerator(qe::RandomGenerator* random) {
	m_random = random;
}

void S_AI::setMapManager(TileMapManager * mapManager) {
	m_mapManager = mapManager;
}