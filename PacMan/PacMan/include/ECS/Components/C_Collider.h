#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

enum class CollisionOrigin { 
	TopLeft, 
	Center 
};

class C_Collider : public qe::C_Base {
public:
	C_Collider() : C_Base(static_cast<qe::ComponentType>(Component::Collider)), m_origin(CollisionOrigin::Center), m_isColliding(false) {}
	virtual ~C_Collider() {}

	const sf::FloatRect& getAABB() const { return m_AABB; }

	void setSize(const sf::Vector2f& vector) { m_AABB.width = vector.x; m_AABB.height = vector.y; }
	
	void setPosition(const sf::Vector2f& vector) {
		if (m_origin == CollisionOrigin::Center) {
			m_AABB.left = vector.x; m_AABB.top = vector.y;
		}
		else {
			m_AABB.left = vector.x + m_AABB.width / 2.0f; m_AABB.top = vector.y + m_AABB.height / 2.0f;
		}
	}

	void isColliding() { m_isColliding = true; }
	void resetCollisionFlag() { m_isColliding = false; }

private:
	CollisionOrigin m_origin;

	sf::FloatRect m_AABB;
	bool m_isColliding;
};