#include "ECS/Systems/S_Collision.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Collider.h"
#include "ECS/Components/C_Position.h"

#include "qe/ECS/SystemManager.h"

S_Collision::S_Collision(qe::SystemManager* systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Collision), systemManager),
	m_mapManager(nullptr) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Position));
	req.set(static_cast<qe::ComponentType>(Component::Collider));
	m_requiredComponents.push_back(req);
}

S_Collision::~S_Collision() = default;

void S_Collision::notify(const qe::Message & message) {}

void S_Collision::update(float dt) {
	auto entityManager = m_systemManager->getEntityManager();

	if (m_mapManager) {
		int tileSize = m_mapManager->getCurrentMap().getTileSize();

		Collisions collisions;

		for (auto& entity : m_entities) {
			C_Position* position = entityManager->getComponent<C_Position>(entity, static_cast<qe::ComponentType>(Component::Position));
			C_Collider* collider = entityManager->getComponent<C_Collider>(entity, static_cast<qe::ComponentType>(Component::Collider));

			// Update the collider
			collider->setPosition(position->getPosition());
			collider->resetCollisionFlag();

			// Check map collisions
			sf::FloatRect aabb = collider->getAABB();
			auto mapPosition = m_mapManager->getPosition();

			int fromX = static_cast<int>(floor((aabb.left - mapPosition.x) / tileSize));
			int toX = static_cast<int>(floor((aabb.left + aabb.width - mapPosition.x) / tileSize));
			int fromY = static_cast<int>(floor((aabb.top - mapPosition.y) / tileSize));
			int toY = static_cast<int>(floor((aabb.top + aabb.height - mapPosition.y) / tileSize));

			for (int x = fromX; x <= toX; ++x) {
				for (int y = fromY; y <= toY; ++y) {
					auto tileId = m_mapManager->getCurrentMap().getMapTile(x, y);
					auto tile = m_mapManager->getCurrentMap().getTileData(tileId);
					
					if (!tile.IsSolid) continue;

					sf::FloatRect tileAABB(static_cast<float>(x * tileSize + mapPosition.x), 
						static_cast<float>(y * tileSize + mapPosition.y), static_cast<float>(tileSize),
						static_cast<float>(tileSize));

					sf::FloatRect intersection;
					aabb.intersects(tileAABB, intersection);

					float area = intersection.width * intersection.height;

					collisions.emplace_back(area, &tile, tileAABB);
				}
			}

			if (!collisions.empty()) {
				std::sort(collisions.begin(), collisions.end(), [](Collision& c1, Collision& c2) {
					return c1.Area > c2.Area;
				});

				for (auto& collision : collisions) {
					auto entityAABB = collider->getAABB();
					if (!entityAABB.intersects(collision.Bounds)) continue;

					float xDiff = (entityAABB.left + entityAABB.width / 2.0f) - (collision.Bounds.left + (collision.Bounds.width / 2.0f));
					float yDiff = (entityAABB.top + entityAABB.height / 2.0f) - (collision.Bounds.top + (collision.Bounds.height / 2.0f));

					float resolver = 0.0f;

					if (std::abs(xDiff) > std::abs(yDiff)) {
						if (xDiff > 0.0f) {
							resolver = collision.Bounds.left + tileSize - entityAABB.left;
						}
						else {
							resolver = -(entityAABB.left + entityAABB.width - collision.Bounds.left);
						}

						position->move(resolver, 0.0f);
						collider->setPosition(position->getPosition());

						m_systemManager->addEvent(entity, static_cast<qe::EntityEventType>(EntityEvent::Colliding_X));
						collider->isColliding();
					}
					else {
						if (yDiff > 0.0f) {
							resolver = collision.Bounds.top + tileSize - entityAABB.top;
						}
						else {
							resolver = -(entityAABB.top + entityAABB.height - collision.Bounds.top);
						}

						position->move(0.0f, resolver);
						collider->setPosition(position->getPosition());

						m_systemManager->addEvent(entity, static_cast<qe::EntityEventType>(EntityEvent::Colliding_Y));
						collider->isColliding();
					}
				}
			}
		}
		// Handle warp (if pacman goes out of bounds, warp to other side)
		// Handle map collisions
	}

	// Handle entity on entity collisions
}

void S_Collision::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}

void S_Collision::setTileMapManager(TileMapManager * mapManager) {
	m_mapManager = mapManager;
}

void S_Collision::render(qe::Window* window) {
	//auto entities = m_systemManager->getEntityManager();
	//auto renderer = window->getRenderWindow();

	//for (auto& entity : m_entities) {
	//	auto collider = entities->getComponent<C_Collider>(entity, static_cast<qe::ComponentType>(Component::Collider));

	//	sf::RectangleShape rect;
	//	rect.setPosition(collider->getAABB().left, collider->getAABB().top);
	//	rect.setSize(sf::Vector2f(collider->getAABB().width, collider->getAABB().height));
	//	rect.setOutlineColor(sf::Color::Green);
	//	rect.setFillColor(sf::Color::Transparent);
	//	rect.setOutlineThickness(1.0f);
	//	renderer->draw(rect);
	//}
}