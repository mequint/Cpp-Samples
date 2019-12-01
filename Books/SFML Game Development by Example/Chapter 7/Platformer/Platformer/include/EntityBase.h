#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

enum class EntityType { Base, Enemy, Player };

enum class EntityState { Idle, Walking, Jumping, Attacking, Hurt, Dying };

struct TileInfo;

struct CollisionElement {
	CollisionElement(float area, TileInfo* info, const sf::FloatRect& bounds) :
		m_area(area), m_tile(info), m_tileBounds(bounds) {}

	float m_area;
	TileInfo* m_tile;
	sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;
bool SortCollisions(const CollisionElement& a, const CollisionElement& b);

class EntityManager;

class EntityBase {
	friend class EntityManager;

public:
	EntityBase(EntityManager* entityManager);
	virtual ~EntityBase();

	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetSize() const;
	EntityState GetState() const;
	std::string GetName() const;
	unsigned int GetId() const;
	EntityType GetType() const;

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f& position);
	void SetSize(float x, float y);
	void SetState(const EntityState& state);

	void Move(float x, float y);
	void AddVelocity(float x, float y);
	void Accelerate(float x, float y);
	void SetAcceleration(float x, float y);
	void ApplyFriction(float x, float y);

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* window) = 0;

protected:
	void UpdateAABB();
	void CheckCollisions();
	void ResolveCollisions();

	virtual void OnEntityCollision(EntityBase* collider, bool attack) = 0;

	std::string m_name;
	EntityType m_type;
	unsigned int m_id;
	sf::Vector2f m_position;
	sf::Vector2f m_positionOld;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_friction;

	TileInfo* m_referenceTile;
	sf::Vector2f m_size;
	sf::FloatRect m_AABB;

	EntityState m_state;

	bool m_collidingOnX;
	bool m_collidingOnY;

	Collisions m_collisions;
	EntityManager* m_entityManager;
};
