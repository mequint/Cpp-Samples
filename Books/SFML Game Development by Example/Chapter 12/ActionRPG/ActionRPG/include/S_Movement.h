#pragma once

#include "S_Base.h"

enum class Axis {x, y};

class Map;

class S_Movement : public S_Base {
public:
	S_Movement(SystemManager* systemManager);
	~S_Movement();

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);

	void SetMap(Map* gameMap);

private:
	void StopEntity(const EntityId& entity, const Axis& axis);
	void SetDirection(const EntityId& entity, const Direction& dir);
	const sf::Vector2f& GetTileFriction(unsigned int elevation, unsigned int x, unsigned int y);

	void MovementStep(float dt, C_Movable* movable, C_Position* position);

	Map* m_gameMap;
};