#include "Canvas.h"

Canvas::Canvas(unsigned int width, unsigned int height, const sf::Color & backgroundColor) :
	m_backgroundColor(backgroundColor) {

	m_image.create(width, height, backgroundColor);
}

void Canvas::clear() {
	m_image.create(m_image.getSize().x, m_image.getSize().y, m_backgroundColor);
}

void Canvas::draw(sf::RenderWindow& window) {
	sf::Texture texture;
	texture.loadFromImage(m_image);
	m_sprite.setTexture(texture);

	window.draw(m_sprite);
}

void Canvas::putPixel(unsigned int x, unsigned int y, sf::Color & color) {
	if (x < 0 || x >= m_image.getSize().x - 1 || y < 0 || y >= m_image.getSize().y - 1) return;

	m_image.setPixel(x, y, color);
}

// Bresenham algorithm with all octaves taken into account: 
//    http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
void Canvas::putLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, sf::Color & color) {
	int w = x2 - x1;
	int h = y2 - y1;
	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;

	if (w < 0) {
		dx1 = -1;
		dx2 = -1;
	}
	else if (w > 0) {
		dx1 = 1;
		dx2 = 1;
	}

	if (h < 0) {
		dy1 = -1;
	}
	else if (h > 0) {
		dy1 = 1;
	}

	int longest = std::abs(w);
	int shortest = std::abs(h);

	if (!(longest > shortest)) {
		longest = std::abs(h);
		shortest = std::abs(w);

		if (h < 0) {
			dy2 = -1;
		}
		else if (h > 0) {
			dy2 = 1;
		}
	}

	int numerator = longest >> 1;
	for (int i = 0; i <= longest; ++i) {
		putPixel(x1, y1, color);

		numerator += shortest;
		if (!(numerator < longest)) {
			numerator -= longest;
			x1 += dx1;
			y1 += dy1;
		}
		else {
			x1 += dx2;
			y1 += dy2;
		}
	}
}

void Canvas::putRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Color & color) {
	for (int i = x; i <= x + width; ++i) {
		putPixel(i, y, color);
		putPixel(i, y + height, color);
	}

	for (int i = y; i < y + height; ++i) {
		putPixel(x, i, color);
		putPixel(x + width, i, color);
	}
}

void Canvas::putFilledRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, sf::Color & color) {
	for (int i = x; i <= x + width; ++i)
	{
		for (int j = y; j <= y + height; ++j) {
			putPixel(i, j, color);
		}
	}
}

void Canvas::putCircle(unsigned int x0, unsigned int y0, unsigned int radius, sf::Color & color) {
	unsigned int x = 0;
	unsigned int y = radius;
	
	int delta = 3 - 2 * static_cast<int>(radius);

	while (x <= y) {
		putPixel(x0 + x, y0 + y, color);
		putPixel(x0 + y, y0 + x, color);
		putPixel(x0 - y, y0 + x, color);
		putPixel(x0 - x, y0 + y, color);
		putPixel(x0 - x, y0 - y, color);
		putPixel(x0 - y, y0 - x, color);
		putPixel(x0 + y, y0 - x, color);
		putPixel(x0 + x, y0 - y, color);

		x += 1;
		if (delta <= 0) {
			delta = delta + 4 * static_cast<int>(x) + 6;
		}
		else {
			delta = delta + 4 * (static_cast<int>(x) - static_cast<int>(y)) + 10;
			y -= 1;
		}
	}
}