#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Rendering a Rectangle");

	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));								// Creating a Rectangle Shape (an extension of a Drawable)
	rectangle.setFillColor(sf::Color::Red);													// ...Change the color
	rectangle.setPosition(320.0f, 240.0f);													// ...Set the position
	rectangle.setOrigin(rectangle.getSize().x / 2.0f, rectangle.getSize().y / 2.0f);		// ...Set the origin

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		window.draw(rectangle);																// Drawing the Rectangle Shape
		window.display();
	}

	return EXIT_SUCCESS;
}