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

	void setSize(const sf::Vector2f& vector) {
		m_AABB.width = vector.x;
		m_AABB.height = vector.y;
	}
	
	void setPosition(const sf::Vector2f& vector) {
		m_AABB.left = vector.x; 
		m_AABB.top = vector.y;
	}

	CollisionOrigin getOrigin() const { return m_origin; }

	void isColliding() { m_isColliding = true; }
	void resetCollisionFlag() { m_isColliding = false; }

private:
	CollisionOrigin m_origin;

	sf::FloatRect m_AABB;
	bool m_isColliding;
};