#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Bouncing Mushroom");
	
	// Load an image file into a Texture
	sf::Texture mushroomTexture;
	mushroomTexture.loadFromFile("Mushroom.png");

	// Retrieve the Texture's size for usage by the Sprite
	sf::Vector2f size = static_cast<sf::Vector2f>(mushroomTexture.getSize());

	sf::Sprite mushroom(mushroomTexture);					// Creating a Sprite using the Mushroom texture as its image
	mushroom.setOrigin(size.x / 2.0f, size.y / 2.0f);		// ...Set the origin to the middle of the texture
	mushroom.setColor(sf::Color(255, 0, 0, 150));			// ...Set the color

	sf::Vector2f increment(0.4f, 0.4f);						// Distance to increment per frame update (this is still pretty fast without the Window Frame Limit set) 

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Check to see if the sprite has exited the window boundaries; negate the increment if so
		if ((mushroom.getPosition().x + size.x / 2.0f > static_cast<float>(window.getSize().x) && increment.x > 0.0f) ||
			(mushroom.getPosition().x - size.x / 2.0f < 0.0f && increment.x < 0.0f)) {
			increment.x = -increment.x;
		}

		if ((mushroom.getPosition().y + size.y / 2.0f > static_cast<float>(window.getSize().y) && increment.y > 0.0f) ||
			(mushroom.getPosition().y - size.y / 2.0f < 0.0f && increment.y < 0.0f)) {
			increment.y = -increment.y;
		}

		// Update the sprites position
		mushroom.setPosition(mushroom.getPosition() + increment);

		window.clear(sf::Color(16, 16, 16, 255));
		window.draw(mushroom);
		window.display();
	}

	return EXIT_SUCCESS;
}