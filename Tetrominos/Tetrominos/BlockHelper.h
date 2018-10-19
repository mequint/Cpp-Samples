#pragma once

#include <SFML/Graphics.hpp>
#include "ShapeType.h"

class BlockHelper
{
	public:
		static sf::Color GetBlockColor(ShapeType type);
};