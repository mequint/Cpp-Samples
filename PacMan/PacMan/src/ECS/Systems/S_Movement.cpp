#include "ECS/Systems/S_Movement.h"

#include <iostream>

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Motion.h"
#include "ECS/Components/C_Position.h"

#include "qe/ECS/SystemManager.h"

S_Movement::S_Movement(qe::SystemManager * systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Movement), systemManager),
	m_timeStep(1.0f / 60.0f),
	m_currentTime(0.0f) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Position));
	req.set(static_cast<qe::ComponentType>(Component::Motion));
	m_requiredComponents.push_back(req);

	m_mapManager = nullptr;

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

			Direction dir = static_cast<Direction>(message.m_int);
			qe::EntityEventType e;

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
	
		switch (motion->getDirection()) {
			case Direction::Up: {
				int nextY = tileY - 1;

				// If the entity is on the board edge, wrap around to the bottom edge
				if (nextY < 0) {
					nextY = currentMap.getHeight() - 1;

					auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, nextY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(tileX * tileSize, nextY * tileSize);

					if (physicalDirection == Direction::Up && position->getPosition().y == m_mapManager->getPosition().y) {
						position->setPosition(tilePosition);
					}
				}
				else {
					auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, nextY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(tileX * tileSize, nextY * tileSize);

					if (!tileData.IsSolid) {
						if (position->getPosition().x == tilePosition.x)
							motion->setVelocity(sf::Vector2f(0.0f, -128.0f));
					}
					else {
						if (physicalDirection == Direction::Up) {
							if (position->getPosition().y <= tilePosition.y + tileSize)
								motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
						}
					}
				}
				break;
			}

			case Direction::Down: {
				int nextY = tileY + 1;

				// If the entity is on the board edge, wrap around to top edge
				if (nextY < 0) {
					nextY = 0;

					auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, nextY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(tileX * tileSize, nextY * tileSize);

					if (physicalDirection == Direction::Down && position->getPosition().y == m_mapManager->getPosition().y + m_mapManager->getMapSize().y - tileSize) {
						position->setPosition(tilePosition);
					}
				}
				else {
					auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, nextY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(tileX * tileSize, nextY * tileSize);

					if (!tileData.IsSolid) {
						if (position->getPosition().x == tilePosition.x)
							motion->setVelocity(sf::Vector2f(0.0f, 128.0f));
					}
					else {
						if (physicalDirection == Direction::Down)
							motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
					}
				}
				break;
			}

			case Direction::Left: {
				int nextX = tileX - 1;

				// If the entity is on the board edge, wrap around to the right side
				if (nextX < 0) {
					nextX = currentMap.getWidth() - 1;

					auto tileData = currentMap.getTileData(currentMap.getMapTile(nextX, tileY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(nextX * tileSize, tileY * tileSize);

					if (physicalDirection == Direction::Left && position->getPosition().x == m_mapManager->getPosition().x) {
						position->setPosition(tilePosition);
					}
				}
				else {
					auto tileData = currentMap.getTileData(currentMap.getMapTile(nextX, tileY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(nextX * tileSize, tileY * tileSize);

					// Otherwise, move like normal
					if (!tileData.IsSolid) {
						if (position->getPosition().y == tilePosition.y)
							motion->setVelocity(sf::Vector2f(-128.0f, 0.0f));
					}
					// Or stop if a wall is hit
					else {
						if (physicalDirection == Direction::Left) {
							if (position->getPosition().x <= tilePosition.x + tileSize)
								motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
						}
					}
				}

				break;
			}

			case Direction::Right: {
				int nextX = tileX + 1;

				// If the entity is on the board edge, wrap around to the left side				
				if (nextX >= currentMap.getWidth()) {
					nextX = 0;
					
					auto tileData = currentMap.getTileData(currentMap.getMapTile(nextX, tileY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(nextX * tileSize, tileY * tileSize);
					
					if (physicalDirection == Direction::Right && position->getPosition().x == m_mapManager->getPosition().x + m_mapManager->getMapSize().x - tileSize) {
						position->setPosition(tilePosition);
					}
				}
				else {
					auto tileData = currentMap.getTileData(currentMap.getMapTile(nextX, tileY));
					auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(nextX * tileSize, tileY * tileSize);

					if (!tileData.IsSolid) {
						if (position->getPosition().y == tilePosition.y)
							motion->setVelocity(sf::Vector2f(128.0f, 0.0f));
					}
					else {
						if (physicalDirection == Direction::Right)
							motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
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

Direction S_Movement::_getPhysicalDirection(const sf::Vector2f& velocity) {
	if (velocity.x < 0.0f) {
		return Direction::Left;
	}
	else if (velocity.x > 0.0f) {
		return Direction::Right;
	}

	if (velocity.y < 0.0f) {
		return Direction::Up;
	}
	else if (velocity.y > 0.0f) {
		return Direction::Down;
	}

	return Direction::None;
}