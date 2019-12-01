#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "First Window!");			// Setup the Window

	while (window.isOpen()) {
		// Handle Window events
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close the Window if the "X" on the top right of the Window is clicked
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);				// Clear the screen
		window.display();							// Display the window and its contents
	}

	return EXIT_SUCCESS;
}