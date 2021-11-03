#include "ECS/Systems/S_Movement.h"

#include <iostream>

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Motion.h"
#include "ECS/Components/C_Position.h"

#include "qe/ECS/SystemManager.h"

S_Movement::S_Movement(qe::SystemManager * systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Movement), systemManager),
	m_timeStep(1.0f / 60.0f),
	m_currentTime(0.0f),
	m_mapManager(nullptr) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Position));
	req.set(static_cast<qe::ComponentType>(Component::Motion));
	m_requiredComponents.push_back(req);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::RequestMove), this);
}

S_Movement::~S_Movement() = default;

void S_Movement::notify(const qe::Message & message) {
	auto entities = m_systemManager->getEntityManager();
	EntityMessage m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::RequestMove: {
			if (!hasEntity(message.m_receiver)) return;

			C_Motion* motion = entities->getComponent<C_Motion>(message.m_receiver, static_cast<qe::ComponentType>(Component::Motion));

			auto dir = static_cast<eDirection>(message.m_int);
			motion->setDirection(dir);
			break;
		}
	}
}

void S_Movement::update(float dt) {
	m_currentTime += dt;
	if (m_currentTime < m_timeStep) return;
	m_currentTime = 0.0f;

	auto entityManager = m_systemManager->getEntityManager();
	auto currentMap = m_mapManager->getCurrentMap();
	auto tileSize = currentMap.getTileSize();

	for (auto& entity : m_entities) {
		auto position = entityManager->getComponent<C_Position>(entity, static_cast<qe::ComponentType>(Component::Position));
		auto motion = entityManager->getComponent<C_Motion>(entity, static_cast<qe::ComponentType>(Component::Motion));
		
		int tileX = static_cast<int>(position->getPosition().x - m_mapManager->getPosition().x) / tileSize;
		int tileY = static_cast<int>(position->getPosition().y - m_mapManager->getPosition().y) / tileSize;

		// Determine the physical direction of the entity
		auto physicalDirection = _getPhysicalDirection(motion->getVelocity());
		auto physicalTile = m_mapManager->getTileData(tileX, tileY, physicalDirection);
		auto physicalTilePosition = _getPosition(m_mapManager->getPosition(), tileX, tileY, tileSize, physicalDirection);

		// Handle wrap around
		if (physicalDirection == eDirection::Right && position->getPosition().x == m_mapManager->getPosition().x + m_mapManager->getMapSize().x - tileSize) {
			position->setPosition(_getPosition(m_mapManager->getPosition(), 0, tileY, tileSize));
			return;
		}
		else if (physicalDirection == eDirection::Left && position->getPosition().x == m_mapManager->getPosition().x) {
			position->setPosition(_getPosition(m_mapManager->getPosition(), currentMap.getWidth() - 1, tileY, tileSize));
			return;
		}

		switch (motion->getDirection()) {
			case eDirection::Up: {
				int nextY = tileY - 1;

				auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, nextY));
				auto tilePosition = _getPosition(m_mapManager->getPosition(), tileX, nextY, tileSize);

				// If the entity is on the board edge, wrap around to the right side
				if (!tileData.IsSolid) {
					if (position->getPosition().x == tilePosition.x)
						motion->setVelocity(sf::Vector2f(0.0f, -128.0f));
				}
				else {
					if (physicalTile.IsSolid && 
						position->getPosition().x <= physicalTilePosition.x + tileSize &&
						position->getPosition().y <= physicalTilePosition.y + tileSize) {
						motion->setVelocity(sf::Vector2f(0.0f, 0.0f));

						qe::Message stopMessage(static_cast<qe::MessageType>(EntityMessage::Stop));
						stopMessage.m_receiver = entity;
						stopMessage.m_int = static_cast<int>(eDirection::Up);

						m_systemManager->getMessageDispatch()->dispatch(stopMessage);
					}
				}

				break;
			}

			case eDirection::Down: {
				int nextY = tileY + 1;

				auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, nextY));
				auto tilePosition = _getPosition(m_mapManager->getPosition(), tileX, nextY, tileSize);

				// If the entity is on the board edge, wrap around to the right side
				if (!tileData.IsSolid) {
					if (position->getPosition().x == tilePosition.x)
						motion->setVelocity(sf::Vector2f(0.0f, 128.0f));
				}
				// Or stop if a wall is hit
				else {
					if (physicalTile.IsSolid &&
						position->getPosition().x <= physicalTilePosition.x + tileSize &&
						position->getPosition().y <= physicalTilePosition.y + tileSize) {
						motion->setVelocity(sf::Vector2f(0.0f, 0.0f));

						qe::Message stopMessage(static_cast<qe::MessageType>(EntityMessage::Stop));
						stopMessage.m_receiver = entity;
						stopMessage.m_int = static_cast<int>(eDirection::Down);

						m_systemManager->getMessageDispatch()->dispatch(stopMessage);
					}
				}

				break;
			}

			case eDirection::Left: {
				int nextX = tileX - 1;

				auto tileData = currentMap.getTileData(currentMap.getMapTile(nextX, tileY));
				auto tilePosition = _getPosition(m_mapManager->getPosition(), nextX, tileY, tileSize);

				// Otherwise, move like normal
				if (!tileData.IsSolid) {
					if (position->getPosition().y == tilePosition.y) {
						motion->setVelocity(sf::Vector2f(-128.0f, 0.0f));
					}
				}
				// Or stop if a wall is hit
				else {
					if (physicalTile.IsSolid &&
						position->getPosition().x <= physicalTilePosition.x + tileSize &&
						position->getPosition().y <= physicalTilePosition.y + tileSize) {
						motion->setVelocity(sf::Vector2f(0.0f, 0.0f));

						qe::Message stopMessage(static_cast<qe::MessageType>(EntityMessage::Stop));
						stopMessage.m_receiver = entity;
						stopMessage.m_int = static_cast<int>(eDirection::Left);

						m_systemManager->getMessageDispatch()->dispatch(stopMessage);
					}
				}

				break;
			}

			case eDirection::Right: {
				int nextX = tileX + 1;

				auto tileData = currentMap.getTileData(currentMap.getMapTile(nextX, tileY));
				auto tilePosition = _getPosition(m_mapManager->getPosition(), nextX, tileY, tileSize);

				if (!tileData.IsSolid) {
					if (position->getPosition().y == tilePosition.y)
						motion->setVelocity(sf::Vector2f(128.0f, 0.0f));
				}
				else {
					if (physicalTile.IsSolid &&
						position->getPosition().x <= physicalTilePosition.x + tileSize &&
						position->getPosition().y <= physicalTilePosition.y + tileSize) {
						motion->setVelocity(sf::Vector2f(0.0f, 0.0f));

						qe::Message stopMessage(static_cast<qe::MessageType>(EntityMessage::Stop));
						stopMessage.m_receiver = entity;
						stopMessage.m_int = static_cast<int>(eDirection::Right);

						m_systemManager->getMessageDispatch()->dispatch(stopMessage);
					}
				}

				break;
			}
		}

		auto velocity = sf::Vector2f(round(motion->getVelocity().x * m_timeStep), round(motion->getVelocity().y * m_timeStep));
		position->move(velocity);
	}
}

void S_Movement::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}

void S_Movement::setMapManager(TileMapManager * mapManager) {
	m_mapManager = mapManager;
}

// ******************** //
// Helper methods		
// ******************** //

eDirection S_Movement::_getPhysicalDirection(const sf::Vector2f& velocity) {
	if (velocity.x < 0.0f) {
		return eDirection::Left;
	}
	else if (velocity.x > 0.0f) {
		return eDirection::Right;
	}

	if (velocity.y < 0.0f) {
		return eDirection::Up;
	}
	else if (velocity.y > 0.0f) {
		return eDirection::Down;
	}

	return eDirection::None;
}

sf::Vector2f S_Movement::_getPosition(const sf::Vector2f & offset, int tileX, int tileY, int tileSize, const eDirection& direction) {
	switch (direction) {
		case eDirection::Up: return offset + sf::Vector2f(static_cast<float>(tileX * tileSize), static_cast<float>((tileY - 1) * tileSize));
		case eDirection::Down: return offset + sf::Vector2f(static_cast<float>(tileX * tileSize), static_cast<float>((tileY + 1) * tileSize));
		case eDirection::Left: return offset + sf::Vector2f(static_cast<float>((tileX - 1) * tileSize), static_cast<float>(tileY * tileSize));
		case eDirection::Right: return offset + sf::Vector2f(static_cast<float>((tileX + 1) * tileSize), static_cast<float>(tileY * tileSize));
	}

	return offset + sf::Vector2f(static_cast<float>(tileX * tileSize), static_cast<float>(tileY * tileSize));
}