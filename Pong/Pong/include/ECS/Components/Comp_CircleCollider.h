//#pragma once
//
//#include <SFML/System/Vector2.hpp>
//
//#include "ECS/Components/Comp_Collider.h"
//
//class Comp_CircleCollider : public Comp_Collider {
//public:
//	Comp_CircleCollider() : Comp_Collider(Component::CircleCollider) {}
//	~Comp_CircleCollider() = default;
//
//	void SetCenter(const sf::Vector2f& pos) { m_center = pos; }
//	void SetCenter(float x, float y) { m_center = sf::Vector2f(x, y); }
//	sf::Vector2f GetCenter() const { return m_center; }
//
//	void SetRadius(float radius) { m_radius = radius; }
//	float GetRadius() { return m_radius; }
//
//private:
//	sf::Vector2f m_center;
//	float m_radius;
//};