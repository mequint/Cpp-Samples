#include "EntityBase.h"

#include "DebugOverlay.h"
#include "EntityManager.h"
#include "Map.h"

bool SortCollisions(const CollisionElement & a, const CollisionElement & b) {
	return a.m_area > b.m_area;
}


EntityBase::EntityBase(EntityManager * entityManager) :
	m_entityManager(entityManager),
	m_name("BaseEntity"),
	m_type(EntityType::Base),
	m_id(0),
	m_referenceTile(nullptr),
	m_state(EntityState::Idle),
	m_collidingOnX(false),
	m_collidingOnY(false) {
}

EntityBase::~EntityBase() = default;

const sf::Vector2f& EntityBase::GetPosition() const { return m_position; }
const sf::Vector2f& EntityBase::GetSize() const { return m_size; }
EntityState EntityBase::GetState() const { return m_state; }
std::string EntityBase::GetName() const { return m_name; }
unsigned int EntityBase::GetId() const { return m_id; }
EntityType EntityBase::GetType() const { return m_type; }

void EntityBase::SetPosition(float x, float y) {
	m_position = sf::Vector2f(x, y);
	UpdateAABB();
}

void EntityBase::SetPosition(const sf::Vector2f & position) {
	m_position = position;
	UpdateAABB();
}

void EntityBase::SetSize(float x, float y) {
	m_size = sf::Vector2f(x, y);
	UpdateAABB();
}

void EntityBase::SetState(const EntityState & state) {
	if (m_state == EntityState::Dying) return;

	m_state = state;
}

void EntityBase::Move(float x, float y) {
	m_positionOld = m_position;
	m_position += sf::Vector2f(x, y);

	sf::Vector2u mapSize = m_entityManager->GetContext()->m_gameMap->GetMapSize();
	if (m_position.x < 0.0f) {
		m_position.x = 0.0f;
	}
	else if (m_position.x > (mapSize.x + 1) * Sheet::Tile_Size) {
		m_position.x = static_cast<float>((mapSize.x + 1) * Sheet::Tile_Size);
	}

	if (m_position.y < 0.0f) {
		m_position.y = 0.0f;
	}
	else if (m_position.y > (mapSize.y + 1) * Sheet::Tile_Size) {
		m_position.y = static_cast<float>((mapSize.y + 1) * Sheet::Tile_Size);
		SetState(EntityState::Dying);
	}

	UpdateAABB();
}

void EntityBase::AddVelocity(float x, float y) {
	m_velocity += sf::Vector2f(x, y);

	if (abs(m_velocity.x) > m_maxVelocity.x) {
		if (m_velocity.x < 0.0f) {
			m_velocity.x = -m_maxVelocity.x;
		}
		else {
			m_velocity.x = m_maxVelocity.x;
		}
	}

	if (abs(m_velocity.x) > m_maxVelocity.y) {
		if (m_velocity.y < 0.0f) {
			m_velocity.y = -m_maxVelocity.y;
		}
		else {
			m_velocity.y = m_maxVelocity.y;
		}
	}
}

void EntityBase::Accelerate(float x, float y) {
	m_acceleration += sf::Vector2f(x, y);
}

void EntityBase::SetAcceleration(float x, float y) {
	m_acceleration = sf::Vector2f(x, y);
}

void EntityBase::ApplyFriction(float x, float y) {
	if (m_velocity.x != 0.0f) {
		if (abs(m_velocity.x) - abs(x) < 0.0f) {
			m_velocity.x = 0.0f;
		}
		else {
			if (m_velocity.x < 0.0f) {
				m_velocity.x += x;
			}
			else {
				m_velocity.x -= x;
			}
		}
	}

	if (m_velocity.y != 0.0f) {
		if (abs(m_velocity.y) - abs(y) < 0.0f) {
			m_velocity.y = 0.0f;
		}
		else {
			if (m_velocity.y < 0.0f) {
				m_velocity.y += y;
			}
			else {
				m_velocity.y -= y;
			}
		}
	}
}

void EntityBase::Update(float dt) {
	Map* map = m_entityManager->GetContext()->m_gameMap;

	float gravity = map->GetGravity();
	Accelerate(0.0f, gravity);
	AddVelocity(m_acceleration.x * dt, m_acceleration.y * dt);
	SetAcceleration(0.0f, 0.0f);

	sf::Vector2f frictionValue;
	if (m_referenceTile) {
		frictionValue = m_referenceTile->m_friction;
		if (m_referenceTile->m_deadly) {
			SetState(EntityState::Dying);
		}
		else if (map->GetDefaultTile()) {
			frictionValue = map->GetDefaultTile()->m_friction;
		}
		else {
			frictionValue = m_friction;
		}
	}

	float frictionX = (m_speed.x * frictionValue.x) * dt;
	float frictionY = (m_speed.y * frictionValue.y) * dt;

	ApplyFriction(frictionX, frictionY);

	sf::Vector2f deltaPos = m_velocity * dt;
	Move(deltaPos.x, deltaPos.y);

	m_collidingOnX = false;
	m_collidingOnY = false;

	CheckCollisions();
	ResolveCollisions();
}

void EntityBase::UpdateAABB() {
	m_AABB = sf::FloatRect(m_position.x - (m_size.x / 2.0f), m_position.y - m_size.y, m_size.x, m_size.y);
}

void EntityBase::CheckCollisions() {
	Map* gameMap = m_entityManager->GetContext()->m_gameMap;

	unsigned int tileSize = gameMap->GetTileSize();

	int fromX = static_cast<int>(floor(m_AABB.left / static_cast<float>(tileSize)));
	int toX = static_cast<int>(floor((m_AABB.left + m_AABB.width) / static_cast<float>(tileSize)));
	int fromY = static_cast<int>(floor(m_AABB.top / static_cast<float>(tileSize)));
	int toY = static_cast<int>(floor((m_AABB.top + m_AABB.height) / static_cast<float>(tileSize)));

	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			Tile* tile = gameMap->GetTile(x, y);
			if (!tile) continue;

			sf::FloatRect tileBounds(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize), 
				static_cast<float>(tileSize), static_cast<float>(tileSize));
			sf::FloatRect intersection;

			m_AABB.intersects(tileBounds, intersection);

			float area = intersection.width * intersection.height;

			CollisionElement e(area, tile->m_properties, tileBounds);
			m_collisions.emplace_back(e);

			if (tile->m_warp && m_type == EntityType::Player) {
				gameMap->LoadNext();
			}
		}
	}
}

void EntityBase::ResolveCollisions() {
	if (!m_collisions.empty()) {
		std::sort(m_collisions.begin(), m_collisions.end(), SortCollisions);

		Map* gameMap = m_entityManager->GetContext()->m_gameMap;
		
		unsigned int tileSize = gameMap->GetTileSize();
		for (auto& iter : m_collisions) {
			if (!m_AABB.intersects(iter.m_tileBounds)) continue;

			// Begin Debug
			if (m_entityManager->GetContext()->m_debugOverlay->Debug()) {
				sf::Vector2f tempPos(iter.m_tileBounds.left, iter.m_tileBounds.top);
				sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));

				rect->setPosition(tempPos);
				rect->setFillColor(sf::Color(255, 255, 0, 150));
				m_entityManager->GetContext()->m_debugOverlay->Add(rect);
			}
			// End Debug

			float xDiff = (m_AABB.left + (m_AABB.width / 2.0f)) - (iter.m_tileBounds.left + (iter.m_tileBounds.width / 2.0f));
			float yDiff = (m_AABB.top + (m_AABB.height / 2.0f)) - (iter.m_tileBounds.top + (iter.m_tileBounds.height / 2.0f));
			float resolve = 0.0f;

			if (abs(xDiff) > abs(yDiff)) {
				if (xDiff > 0.0f) {
					resolve = (iter.m_tileBounds.left + tileSize) - m_AABB.left;
				}
				else {
					resolve = -((m_AABB.left + m_AABB.width) - iter.m_tileBounds.left);
				}

				Move(resolve, 0.0f);
				m_velocity.x = 0.0f;
				m_collidingOnX = true;
			}
			else {
				if (yDiff > 0.0f) {
					resolve = (iter.m_tileBounds.top + tileSize) - m_AABB.top;
				}
				else {
					resolve = -((m_AABB.top + m_AABB.height) - iter.m_tileBounds.top);
				}

				Move(0.0f, resolve);
				m_velocity.y = 0.0f;
				if (m_collidingOnY) continue;

				m_referenceTile = iter.m_tile;
				m_collidingOnY = true;
			}
		}

		m_collisions.clear();
	}

	if (!m_collidingOnY) {
		m_referenceTile = nullptr;
	}
}