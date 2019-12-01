#include "S_Collision.h"
#include "SystemManager.h"
#include "Map.h"

S_Collision::S_Collision(SystemManager* systemManager) :
	S_Base(System::Collision, systemManager) {

	Bitmask req;
	req.TurnOnBit(static_cast<unsigned int>(Component::Position));
	req.TurnOnBit(static_cast<unsigned int>(Component::Collidable));
	m_requiredComponents.push_back(req);

	req.Clear();

	m_gameMap = nullptr;
}

S_Collision::~S_Collision() = default;

void S_Collision::SetMap(Map * map) { m_gameMap = map; }

void S_Collision::Update(float dt) {
	if (!m_gameMap) return;

	EntityManager* entities = m_systemManager->GetEntityManager();
	for (auto& entity : m_entities) {
		C_Position* position = entities->GetComponent<C_Position>(entity, Component::Position);
		C_Collidable* collidable = entities->GetComponent<C_Collidable>(entity, Component::Collidable);

		collidable->SetPosition(position->GetPosition());
		collidable->ResetCollisionFlags();

		CheckOutOfBounds(position, collidable);
		MapCollisions(entity, position, collidable);
	}

	EntityCollisions();
}

void S_Collision::HandleEvent(const EntityId& entity, const EntityEvent& event) {
}

void S_Collision::Notify(const Message& message) {
}

void S_Collision::EntityCollisions() {
	EntityManager* entities = m_systemManager->GetEntityManager();
	
	for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter) {
		for (auto iter2 = std::next(iter); iter2 != m_entities.end(); ++iter2) {
			C_Collidable* collidable1 = entities->GetComponent<C_Collidable>(*iter, Component::Collidable);
			C_Collidable* collidable2 = entities->GetComponent<C_Collidable>(*iter2, Component::Collidable);

			if (collidable1->GetCollidable().intersects(collidable2->GetCollidable())) {
				// Entity-on-entity collision
			}
		}
	}
}

void S_Collision::MapCollisions(const EntityId& entity, C_Position* pos, C_Collidable* col) {
	unsigned int tileSize = m_gameMap->GetTileSize();

	Collisions c;

	sf::FloatRect entityAABB = col->GetCollidable();

	int fromX = static_cast<int>(floor(entityAABB.left / tileSize));
	int toX = static_cast<int>(floor((entityAABB.left + entityAABB.width) / tileSize));
	int fromY = static_cast<int>(floor(entityAABB.top / tileSize));
	int toY = static_cast<int>(floor((entityAABB.top + entityAABB.height) / tileSize));

	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			for (int l = 0; l < Sheet::Num_Layers; ++l) {
				Tile* t = m_gameMap->GetTile(x, y, l);
				if (!t) continue;
				if (!t->m_solid) continue;

				sf::FloatRect tileAABB(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize), 
					static_cast<float>(tileSize), static_cast<float>(tileSize));
				sf::FloatRect intersection;

				entityAABB.intersects(tileAABB, intersection);

				float s = intersection.width * intersection.height;

				c.emplace_back(s, t->m_properties, tileAABB);
				break;
			}
		}
	}

	if (c.empty()) return;
	std::sort(c.begin(), c.end(), [](CollisionElement& c1, CollisionElement& c2) {
		return c1.m_area > c2.m_area;
	});

	for (auto& coll : c) {
		entityAABB = col->GetCollidable();
		if (!entityAABB.intersects(coll.m_tileBounds)) continue;

		float xDiff = (entityAABB.left + entityAABB.width / 2.0f) - (coll.m_tileBounds.left + (coll.m_tileBounds.width / 2.0f));
		float yDiff = (entityAABB.top + entityAABB.height / 2.0f) - (coll.m_tileBounds.top + (coll.m_tileBounds.height / 2.0f));
		float resolve = 0.0f;

		if (std::abs(xDiff) > std::abs(yDiff)) {
			if (xDiff > 0.0f) {
				resolve = (coll.m_tileBounds.left + tileSize) - entityAABB.left;
			}
			else {
				resolve = -((entityAABB.left + entityAABB.width) - coll.m_tileBounds.left);
			}

			pos->MoveBy(resolve, 0.0f);
			col->SetPosition(pos->GetPosition());

			m_systemManager->AddEvent(entity, static_cast<EventId>(EntityEvent::Colliding_X));
			col->CollideOnX();
		}
		else {
			if (yDiff > 0.0f) {
				resolve = (coll.m_tileBounds.top + tileSize) - entityAABB.top;
			}
			else {
				resolve = -((entityAABB.top + entityAABB.height) - coll.m_tileBounds.top);
			}

			pos->MoveBy(0.0f, resolve);
			col->SetPosition(pos->GetPosition());

			m_systemManager->AddEvent(entity, static_cast<EventId>(EntityEvent::Colliding_Y));
			col->CollideOnY();
		}
	}
}

void S_Collision::CheckOutOfBounds(C_Position* pos, C_Collidable* col) {
	unsigned int tileSize = m_gameMap->GetTileSize();

	if (pos->GetPosition().x < 0.0f) {
		pos->SetPosition(0.0f, pos->GetPosition().y);
		col->SetPosition(pos->GetPosition());
	}
	// Magic number 0.1f is a small adjustment to protect against a rendering bug...
	// Once a repro is determined, remove the magic number
	// ...The spritesheet drawable is not being updated...
	// ...TODO: Create an out-of-bounds event that requires the renderer to update the sprite position
	else if (pos->GetPosition().x > m_gameMap->GetMapSize().x * tileSize - 0.1f) {
		pos->SetPosition(static_cast<float>(m_gameMap->GetMapSize().x * tileSize - 0.1f), pos->GetPosition().y);
		col->SetPosition(pos->GetPosition());
	}

	if (pos->GetPosition().y < 0.0f) {
		pos->SetPosition(pos->GetPosition().x, 0.0f);
		col->SetPosition(pos->GetPosition());
	}
	// Magic number 0.1f is a small adjustment to protect against a rendering bug...
	// Once a repro is determined, remove the magic number
	// ...The spritesheet drawable is not being updated...
	// ...TODO: Create an out-of-bounds event that requires the renderer to update the sprite position
	else if (pos->GetPosition().y > m_gameMap->GetMapSize().y * tileSize - 0.1f) {
		pos->SetPosition(pos->GetPosition().x, static_cast<float>(m_gameMap->GetMapSize().y * tileSize - 0.1f));
		col->SetPosition(pos->GetPosition());
	}
}