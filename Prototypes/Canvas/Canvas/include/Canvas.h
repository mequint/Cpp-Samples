#pragma once

#include <SFML/Graphics.hpp>

class Canvas {
public:
	Canvas(unsigned int width, unsigned int height, const sf::Color& backgroundColor = sf::Color::Transparent);

	void clear();
	void draw(sf::RenderWindow& window);

	void putPixel(unsigned int x, unsigned int y, sf::Color& color);
	void putLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, sf::Color& color);
	void putRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Color& color);
	void putFilledRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Color& color);

	void putCircle(unsigned int x0, unsigned int y0, unsigned int radius, sf::Color& color);

private:
	sf::Image m_image;
	sf::Color m_backgroundColor;

	sf::Sprite m_sprite;
};