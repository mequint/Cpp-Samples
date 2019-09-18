#pragma once

#include <SFML/Graphics.hpp>
#include "qe/ECS/Core/Comp_Base.h"

class Comp_Drawable : public qe::Comp_Base
{
	public:
		Comp_Drawable(const Component& type) : Comp_Base(type) {}
		virtual ~Comp_Drawable() {}

		virtual void SetPosition(const sf::Vector2f& vec) = 0;
		virtual sf::Vector2u GetSize() const = 0;
		virtual void Draw(sf::RenderWindow* window) = 0;
};