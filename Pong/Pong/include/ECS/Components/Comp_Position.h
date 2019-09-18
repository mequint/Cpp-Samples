#pragma once

#include <SFML/System/Vector2.hpp>

#include "qe/ECS/Core/Comp_Base.h"

class Comp_Position : public qe::Comp_Base {
public:
	Comp_Position() : Comp_Base(Component::Position), m_layer(0) {}
	~Comp_Position() = default;

	sf::Vector2f GetPosition() const { return m_position; }
	sf::Vector2f GetOldPosition() const { return m_oldPosition; }
	unsigned int GetLayer() const { return m_layer; }

	void SetPosition(float x, float y) {
		m_oldPosition = m_position;
		m_position = sf::Vector2f(x, y);
	}

	void SetPosition(const sf::Vector2f& vector) {
		m_oldPosition = m_position;
		m_position = vector;
	}

	void SetLayer(unsigned int layer) {
		m_layer = layer;
	}

	void Move(float x, float y) {
		m_oldPosition = m_position;
		m_position += sf::Vector2f(x, y);
	}

	void Move(const sf::Vector2f& vector) {
		m_oldPosition = m_position;
		m_position += vector;
	}

private:
	sf::Vector2f m_position;
	sf::Vector2f m_oldPosition;

	unsigned int m_layer;
};