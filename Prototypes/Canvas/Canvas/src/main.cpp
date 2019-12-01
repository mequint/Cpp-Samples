#include <SFML/Graphics.hpp>

#include "Canvas.h"
#include "RandomGenerator.h"

sf::Color RandomColor(RandomGenerator& random) {
	int number = random.Generate(0, 6);

	switch (number) {
		case 0: return sf::Color::Red;
		case 1: return sf::Color::Green;
		case 2: return sf::Color::Blue;
		case 3: return sf::Color::Cyan;
		case 4: return sf::Color::Yellow;
		case 5: return sf::Color::Magenta;
		case 6: return sf::Color::White;
	}

	return sf::Color::Black;
}

unsigned int Clamp(unsigned int min, unsigned int max, unsigned int value) {
	if (value < min) return min;
	if (value > max) return max;

	return value;
}

int main() {
	const unsigned int width = 800;
	const unsigned int height = 600;

	sf::RenderWindow window(sf::VideoMode(width, height), "Canvas");
	window.setFramerateLimit(30);

	Canvas canvas(width, height);

	RandomGenerator random;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}

				if (event.key.code == sf::Keyboard::Space) {
					canvas.clear();
				}
			}
		}

		auto color = RandomColor(random);

		// Draw Pixels
		//canvas.putPixel(static_cast<unsigned int>(random.Generate(0, width - 1)),
		//	static_cast<unsigned int>(random.Generate(0, height - 1)), color);

		// Draw Lines
		//canvas.putLine(
		//	static_cast<unsigned int>(random.Generate(0, width - 1)),
		//	static_cast<unsigned int>(random.Generate(0, height - 1)),
		//	static_cast<unsigned int>(random.Generate(0, width - 1)),
		//	static_cast<unsigned int>(random.Generate(0, height - 1)),
		//	color);

		// Draw Rects
		//canvas.putFilledRect(
		//	static_cast<unsigned int>(random.Generate(0, width - 1)),
		//	static_cast<unsigned int>(random.Generate(0, height - 1)),
		//	static_cast<unsigned int>(random.Generate(0, width - 1)),
		//	static_cast<unsigned int>(random.Generate(0, height - 1)),
		//	color);

		// Draw circle
		canvas.putCircle(
			static_cast<unsigned int>(random.Generate(0, width - 1)),
			static_cast<unsigned int>(random.Generate(0, height - 1)),
			static_cast<unsigned int>(random.Generate(1, 100)),
			color);

		window.clear();
		canvas.draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}