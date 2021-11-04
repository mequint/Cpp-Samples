#pragma once

#include <SFML/System/Vector2.hpp>

#include "Utilities/eDirections.h"
#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Motion : public qe::C_Base {
public:
	C_Motion() : C_Base(static_cast<qe::ComponentType>(Component::Motion)) {}

	sf::Vector2f getVelocity() { return m_velocity; }
	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }

	eDirection getDirection() const { return m_direction; }
	void setDirection(const eDirection& direction) { m_direction = direction; }

private:
	sf::Vector2f m_velocity;
	eDirection m_direction;
};