#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "qe/ECS/Core/Comp_Base.h"

//class Comp_Collider : public qe::Comp_Base {
//public:
//	Comp_Collider(const Component& type) : Comp_Base(type) {}
//	virtual ~Comp_Collider() {}
//
//	bool IsBouncy() const { return m_isBouncy; }
//	bool IsCollidingOnX() const { return m_isCollidingOnX; }
//	bool IsCollidingOnY() const { return m_isCollidingOnY; }
//
//private:
//	bool m_isBouncy;
//
//	bool m_isCollidingOnX;
//	bool m_isCollidingOnY;
//};

class Comp_Collider : public qe::Comp_Base {
public:
	Comp_Collider() : Comp_Base(Component::Collider), m_collidingOnX(false), m_collidingOnY(false) {}

	const sf::FloatRect& GetAABB() const { return m_AABB; }
	bool IsCollidingOnX() const { return m_collidingOnX; }
	bool IsCollidingOnY() const { return m_collidingOnY; }
	bool IsBouncy() const { return m_isBouncy; }

	void SetAABB(const sf::FloatRect& rect) { m_AABB = rect; }
	void SetSize(const sf::Vector2f& vector) { m_AABB.width = vector.x; m_AABB.height = vector.y; }
	void SetPosition(const sf::Vector2f& vector) { m_AABB.left = vector.x; m_AABB.top = vector.y; }
	void SetIsBouncy(bool isBouncy) { m_isBouncy = isBouncy; }

	void CollideOnX() { m_collidingOnX = true; }
	void CollideOnY() { m_collidingOnY = true; }
	
	void ResetCollisionFlags() {
		m_collidingOnX = false;
		m_collidingOnY = false;
	}

private:
	sf::FloatRect m_AABB;

	bool m_isBouncy;

	bool m_collidingOnX;
	bool m_collidingOnY;
};