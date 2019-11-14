#include <iostream>
#include "AnimatedMessageBox.h"

const std::string loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Message Box");

	sf::Font font;
	std::string fontFile = "../media/Fonts/arial.ttf";
	if (!font.loadFromFile(fontFile)) {
		std::cout << "Failed to load font " << fontFile << std::endl;
		return EXIT_FAILURE;
	}

	AnimatedMessageBox messageBox(font, 300, 200);
	messageBox.setText(loremIpsum, 18, sf::Color::White);
	messageBox.setPosition(sf::Vector2f(250.0f, 200.0f));
	messageBox.setCharPerSeconds(30);

	sf::Clock clock;
	float elapsedTime = 0.0f;

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
				else if (event.key.code == sf::Keyboard::Space) {
					if (!messageBox.isRunning()) {
						messageBox.play();
					}
					else if (messageBox.isRunning() && !messageBox.endOfBlock()) {
						messageBox.skipAnimation();
					}
					else {
						messageBox.nextStringBlock();
					}
				}
				else if (event.key.code == sf::Keyboard::P) {
					messageBox.stop();
				}
				else if (event.key.code == sf::Keyboard::R) {
					messageBox.reset();
				}
			}
		}

		float updateTime = clock.getElapsedTime().asSeconds();
		messageBox.update(elapsedTime);

		window.clear();
		messageBox.draw(window);
		window.display();

		elapsedTime = clock.restart().asSeconds();
	}

	return EXIT_SUCCESS;
}