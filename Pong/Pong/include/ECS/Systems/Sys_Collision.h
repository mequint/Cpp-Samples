#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "qe/ECS/Core/Sys_Base.h"

#include "ECS/Components/Comp_Collider.h"
#include "ECS/Components/Comp_Position.h"
#include "Utilities/Directions.h"

class Sys_Collision : public qe::Sys_Base {
public:
	Sys_Collision(qe::SystemManager* systemManager);
	~Sys_Collision();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& id, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);

	void SetBoundary(const sf::FloatRect& rect);

private:
	void CheckOutOfBounds(const qe::EntityId& entity, Comp_Position* pos, Comp_Collider* collidable);
	Comp_Collider* GetColliderFromType(const qe::EntityId& entityId);

	qe::Bitmask m_colliderTypes;

	sf::FloatRect m_boundary;
};