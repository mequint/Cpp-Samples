#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Drawable : public qe::C_Base {
public:
	C_Drawable(const Component& type) : C_Base(static_cast<qe::ComponentType>(type)) {}
	virtual ~C_Drawable() {}

	// 1.0
	virtual sf::Vector2u getSize() const = 0;
	virtual void setPosition(const sf::Vector2f& vector) = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual void draw(sf::RenderTarget* target) = 0;
};