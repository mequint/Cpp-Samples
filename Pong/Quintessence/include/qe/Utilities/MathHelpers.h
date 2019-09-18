#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace qe {
	namespace math {
		inline float GetMagnitude(const sf::Vector2f& vector) {
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		inline sf::Vector2f GetNormal(sf::Vector2f& vector) {
			float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

			sf::Vector2f normal(vector.x / magnitude, vector.y / magnitude);
			return normal;
		}

		inline float Dot(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}
	}
}