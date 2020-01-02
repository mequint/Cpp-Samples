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

	for (auto& entity : m_entities) {
		auto position = entityManager->getComponent<C_Position>(entity, static_cast<qe::ComponentType>(Component::Position));
		auto motion = entityManager->getComponent<C_Motion>(entity, static_cast<qe::ComponentType>(Component::Motion));
		
		int tileX = static_cast<int>(position->getPosition().x - m_mapManager->getPosition().x) / currentMap.getTileSize();
		int tileY = static_cast<int>(position->getPosition().y - m_mapManager->getPosition().y) / currentMap.getTileSize();

		// Determine the physical direction 
		Direction physicalDirection = Direction::None;
		if (motion->getVelocity().x < 0.0f) {
			physicalDirection = Direction::Left;
		}
		else if (motion->getVelocity().x > 0.0f) {
			physicalDirection = Direction::Right;
		}

		if (motion->getVelocity().y < 0.0f) {
			physicalDirection = Direction::Up;
		}
		else if (motion->getVelocity().y > 0.0f) {
			physicalDirection = Direction::Down;
		}

		// Handle movement step
		switch (motion->getDirection()) {
			case Direction::Up: {
				auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, tileY - 1));
				auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(tileX * currentMap.getTileSize(), (tileY - 1) * currentMap.getTileSize());

				if (!tileData.IsSolid) {
						if (position->getPosition().x == tilePosition.x)
							motion->setVelocity(sf::Vector2f(0.0f, -128.0f));
				}
				else {
					if (physicalDirection == Direction::Up) {
						if (position->getPosition().y <= tilePosition.y + currentMap.getTileSize())
							motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
					}
				}
				break;
			}

			case Direction::Down: {
				auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX, tileY + 1));
				auto tilePosition = m_mapManager->getPosition() + sf::Vector2f(tileX * currentMap.getTileSize(), (tileY + 1) * currentMap.getTileSize());

				if (!tileData.IsSolid) {
					if (position->getPosition().x == tilePosition.x)
						motion->setVelocity(sf::Vector2f(0.0f, 128.0f));
				}
				else {
					if (physicalDirection == Direction::Down) {
						motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
					}
				}
				break;
			}

			case Direction::Left: {
				auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX - 1, tileY));
				auto tilePosition = m_mapManager->getPosition() + sf::Vector2f((tileX - 1) * currentMap.getTileSize(), tileY * currentMap.getTileSize());

				if (!tileData.IsSolid) {
						if (position->getPosition().y == tilePosition.y)
							motion->setVelocity(sf::Vector2f(-128.0f, 0.0f));
				}
				else {
					if (physicalDirection == Direction::Left) {
						if (position->getPosition().x <= tilePosition.x + currentMap.getTileSize())
							motion->setVelocity(sf::Vector2f(0.0f, 0.0f));
					}
				}
				break;
			}

			case Direction::Right: {
				auto tileData = currentMap.getTileData(currentMap.getMapTile(tileX + 1, tileY));
				auto tilePosition = m_mapManager->getPosition() + sf::Vector2f((tileX + 1) * currentMap.getTileSize(), tileY * currentMap.getTileSize());
				
				if (!tileData.IsSolid) {
					if (position->getPosition().y == tilePosition.y)
						motion->setVelocity(sf::Vector2f(128.0f, 0.0f));
				}
				else {
					if (physicalDirection == Direction::Right) {
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