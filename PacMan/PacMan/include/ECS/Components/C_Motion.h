#pragma once

#include <SFML/System/Vector2.hpp>

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Motion : public qe::C_Base {
public:
	C_Motion() : C_Base(static_cast<qe::ComponentType>(Component::Motion)) {}

	sf::Vector2f getVelocity() const { return m_velocity; }
	void setVelocity(const sf::Vector2f& vector) { m_velocity = vector; }
	void setVelocity(float x, float y) { m_velocity = sf::Vector2f(x, y); }

private:
	sf::Vector2f m_velocity;
};