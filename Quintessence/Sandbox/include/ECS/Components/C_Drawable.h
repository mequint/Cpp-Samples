#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "ECS/ECSTypes.h"
#include "qe/ECS/C_Base.h"

class C_Drawable : public qe::C_Base {
public:
	C_Drawable(const Component& type) : C_Base(static_cast<qe::ComponentType>(type)) {}
	virtual ~C_Drawable() {}

	virtual void setPosition(const sf::Vector2f& vector) = 0;
	virtual void draw(sf::RenderTarget* target) = 0;
};