#pragma once

#include "qe/ECS/C_Base.h"
#include <SFML/Graphics/Rect.hpp>

class C_Collider : public qe::C_Base {
public:
	C_Collider() : C_Base(static_cast<qe::ComponentType>(Component::Collider)) {}

	sf::FloatRect getAABB() const { return m_aabb; }
	void setAABB(const sf::FloatRect& rect) { m_aabb = rect; }

	void setPosition(const sf::Vector2f& pos) {
		m_aabb.left = pos.x;
		m_aabb.top = pos.y;
	}

	void setSize(const sf::Vector2f& size) {
		m_aabb.width = size.x;
		m_aabb.height = size.y;
	}

	bool isColliding() const { return m_colliding; }
	void setColliding(bool colliding) { m_colliding = colliding; }

private:
	sf::FloatRect m_aabb;
	bool m_colliding;
};