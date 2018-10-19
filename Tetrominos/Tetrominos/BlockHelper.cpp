#include "BlockHelper.h"

sf::Color BlockHelper::GetBlockColor(ShapeType type)
{
	switch (type)
	{
		case ShapeType::I: return sf::Color::Cyan;
		case ShapeType::J: return sf::Color::Blue;
		case ShapeType::L: return sf::Color(255, 165, 0);
		case ShapeType::O: return sf::Color::Yellow;
		case ShapeType::S: return sf::Color::Green;
		case ShapeType::T: return sf::Color(128, 0, 128);
		case ShapeType::Z: return sf::Color::Red;
	}

	return sf::Color::Magenta;
}