//#pragma once
//
//#include <SFML/Graphics/Rect.hpp>
//#include "ECS/Components/Comp_Collider.h"
//
//class Comp_BoxCollider : public Comp_Collider {
//public:
//	Comp_BoxCollider() : Comp_Collider(Component::BoxCollider) {}
//	~Comp_BoxCollider() = default;
//
//	void SetCenter(const sf::Vector2f& center) { m_center = center; }
//	void SetCenter(float x, float y) { m_center = sf::Vector2f(x, y); }
//	void SetSize(const sf::Vector2f& size) { m_center = size; }
//	void SetSize(float x, float y) { m_center = sf::Vector2f(x, y); }
//
//	sf::Vector2f GetCenter() const { return m_center; }
//	sf::Vector2f GetSize() const { return m_size; }
//	float GetWidth() const { return m_size.x; }
//	float GetHeight() const { return m_size.y; }
//
//private:
//	sf::Vector2f m_center;
//	sf::Vector2f m_size;
//};