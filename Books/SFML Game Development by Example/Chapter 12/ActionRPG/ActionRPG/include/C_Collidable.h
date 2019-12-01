#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "C_Base.h"

enum class Origin { Top_Left, Abs_Center, Mid_Bottom };

class C_Collidable : public C_Base {
public:
	C_Collidable() :
		C_Base(Component::Collidable),
		m_origin(Origin::Mid_Bottom),
		m_collidingOnX(false),
		m_collidingOnY(false) {}

	void ReadIn(std::stringstream& stream) {
		unsigned int origin = 0;
		stream >> m_AABB.width >> m_AABB.height >> m_offset.x >> m_offset.y >> origin;

		m_origin = static_cast<Origin>(origin);
	}

	const sf::FloatRect& GetCollidable() { return m_AABB; }
	bool IsCollidingOnX() { return m_collidingOnX; }
	bool IsCollidingOnY() { return m_collidingOnY; }

	void CollideOnX() { m_collidingOnX = true; }
	void CollideOnY() { m_collidingOnY = true; }

	void ResetCollisionFlags() {
		m_collidingOnX = false;
		m_collidingOnY = false;
	}

	void SetCollidable(const sf::FloatRect& rect) { m_AABB = rect; }
	void SetOrigin(const Origin& origin) { m_origin = origin; }

	void SetSize(const sf::Vector2f& vec) {
		m_AABB.width = vec.x;
		m_AABB.height = vec.y;
	}

	void SetPosition(const sf::Vector2f& vec) {
		switch (m_origin) {
			case Origin::Top_Left:
				m_AABB.left = vec.x + m_offset.x;
				m_AABB.top = vec.y + m_offset.y;
				break;

			case Origin::Abs_Center:
				m_AABB.left = vec.x - (m_AABB.width / 2.0f) + m_offset.x;
				m_AABB.top = vec.y - (m_AABB.height / 2.0f) + m_offset.y;
				break;

			case Origin::Mid_Bottom:
				m_AABB.left = vec.x - (m_AABB.width / 2.0f) + m_offset.x;
				m_AABB.top = vec.y - m_AABB.height + m_offset.y;
				break;
		}
	}

private:
	sf::FloatRect m_AABB;
	sf::Vector2f m_offset;
	Origin m_origin;

	bool m_collidingOnX;
	bool m_collidingOnY;
};