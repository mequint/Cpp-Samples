#pragma once

#include <SFML/System/Vector2.hpp>

#include "Utilities/Directions.h"
#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Motion : public qe::C_Base {
public:
	C_Motion() : C_Base(static_cast<qe::ComponentType>(Component::Motion)) {}

	sf::Vector2f getVelocity() const { return m_velocity; }
	sf::Vector2f getLastVelocity() const { return m_lastVelocity; }

	void setVelocity(const sf::Vector2f& vector) { m_lastVelocity = m_velocity;  m_velocity = vector; }
	void setVelocity(float x, float y) { m_lastVelocity = m_velocity;  m_velocity = sf::Vector2f(x, y); }

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_lastVelocity;

	Direction m_direction;
};