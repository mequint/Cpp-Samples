#pragma once

#include <SFML/System/Vector2.hpp>
#include "C_Base.h"
#include "Directions.h"

class C_Movable : public C_Base {
public:
	C_Movable() :
		C_Base(Component::Movable),
		m_velocityMax(0.0f),
		m_direction(static_cast<Direction>(0)) {}

	void ReadIn(std::stringstream& stream) {
		stream >> m_velocityMax >> m_speed.x >> m_speed.y;

		unsigned int dir = 0;
		stream >> dir;
		m_direction = static_cast<Direction>(dir);
	}

	const sf::Vector2f& GetVelocity() { return m_velocity; }
	float GetMaxVelocity() { return m_velocityMax; }
	const sf::Vector2f& GetSpeed() { return m_speed; }
	const sf::Vector2f& GetAcceleration() { return m_acceleration; }
	Direction GetDirection() { return m_direction; }

	void SetVelocity(const sf::Vector2f& vec) { m_velocity = vec; }
	void SetMaxVelocity(float vel) { m_velocityMax = vel; }
	void SetSpeed(const sf::Vector2f& vec) { m_speed = vec; }
	void SetAcceleration(const sf::Vector2f& vec) { m_acceleration = vec; }
	void SetDirection(const Direction& dir) { m_direction = dir; }

	void AddVelocity(const sf::Vector2f& vec) {
		m_velocity += vec;
		if (std::abs(m_velocity.x) > m_velocityMax) {
			m_velocity.x = m_velocityMax * (m_velocity.x / std::abs(m_velocity.x));
		}

		if (std::abs(m_velocity.y) > m_velocityMax) {
			m_velocity.y = m_velocityMax * (m_velocity.y / std::abs(m_velocity.y));
		}
	}

	void ApplyFriction(const sf::Vector2f& vec) {
		if (m_velocity.x != 0.0f && vec.x != 0.0f) {
			if (std::abs(m_velocity.x) - std::abs(vec.x) < 0.0f) {
				m_velocity.x = 0;
			}
			else {
				m_velocity.x += (m_velocity.x > 0.0 ? -vec.x : vec.x);
			}
		}

		if (m_velocity.y != 0.0f && vec.y != 0.0f) {
			if (std::abs(m_velocity.y) - std::abs(vec.y) < 0.0f) {
				m_velocity.y = 0;
			}
			else {
				m_velocity.y += (m_velocity.y > 0.0f ? -vec.y : vec.y);
			}
		}
	}

	void Accelerate(const sf::Vector2f& vec) { m_acceleration += vec; }
	void Accelerate(float x, float y) { m_acceleration += sf::Vector2f(x, y); }

	void Move(const Direction& dir) {
		if (dir == Direction::Up) {
			m_acceleration.y -= m_speed.y;
		}
		else if (dir == Direction::Down) {
			m_acceleration.y += m_speed.y;
		}
		else if (dir == Direction::Left) {
			m_acceleration.x -= m_speed.x;
		}
		else if (dir == Direction::Right) {
			m_acceleration.x += m_speed.x;
		}
	}

private:
	sf::Vector2f m_velocity;
	float m_velocityMax;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;
	Direction m_direction;
};