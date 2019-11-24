#pragma once

#include "S_Base.h"

struct TileInfo;
class Map;

struct CollisionElement {
	CollisionElement(float area, TileInfo* info, const sf::FloatRect& bounds) :
		m_area(area),
		m_tile(info),
		m_tileBounds(bounds) {}

	float m_area;
	TileInfo* m_tile;
	sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;

class S_Collision : public S_Base {
public:
	S_Collision(SystemManager* systemManager);
	~S_Collision();

	void SetMap(Map* map);

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);

private:
	void EntityCollisions();
	void MapCollisions(const EntityId& entity, C_Position* pos, C_Collidable* col);
	void CheckOutOfBounds(C_Position* pos, C_Collidable* col);

	Map* m_gameMap;
};