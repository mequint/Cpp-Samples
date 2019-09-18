#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "qe/ECS/Core/Comp_Base.h"

#include "Utilities/Directions.h"

class Comp_Motion : public qe::Comp_Base {
	public:
		Comp_Motion() : Comp_Base(Component::Motion) {}

		sf::Vector2f GetVelocity() const { return m_velocity; }
		void SetVelocity(const sf::Vector2f& vector) { m_velocity = vector; }

		bool IsBouncy() const { return m_isBouncy; }
		void SetIsBouncy(bool isBouncy) { m_isBouncy = isBouncy; }

	private:
		sf::Vector2f m_velocity;

		bool m_isBouncy;
};