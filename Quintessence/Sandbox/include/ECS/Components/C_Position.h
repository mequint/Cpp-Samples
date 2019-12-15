#pragma once

#include <SFML/System/Vector2.hpp>

#include "ECS/ECSTypes.h"
#include "qe/ECS/C_Base.h"

class C_Position : public qe::C_Base {
public:
	C_Position() : qe::C_Base(static_cast<qe::ComponentType>(Component::Position)) {}
	~C_Position() = default;

	sf::Vector2f getPosition() const { return m_position; }

	void setPosition(float x, float y) {
		m_position = sf::Vector2f(x, y);
	}
	
	void setPosition(const sf::Vector2f& vector) {
		m_position = vector;
	}

	void move(float x, float y) {
		m_position += sf::Vector2f(x, y);
	}

	void move(const sf::Vector2f& vector) {
		m_position += vector;
	}

private:
	sf::Vector2f m_position;
};