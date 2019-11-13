#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

class MessageBox {
public:
	MessageBox(sf::Font& font, unsigned int width, unsigned int height) {
		m_box.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
		m_box.setFillColor(sf::Color::Transparent);
		m_box.setOutlineThickness(1.0f);

		m_text.setFont(font);
	}

	void setPosition(const sf::Vector2f& pos) {
		m_box.setPosition(pos);
		m_text.setPosition(pos);
	}

	void setText(std::string& text, unsigned int fontSize, const sf::Color& color = sf::Color::Black) {
		m_text.setString(text);
		m_text.setCharacterSize(fontSize);
		m_text.setFillColor(color);

		m_box.setOutlineColor(color);
	}

	void update(float dt) {

	}

	void draw(sf::RenderWindow& window) {
		window.draw(m_box);
		window.draw(m_text);
	}

protected:
	sf::Text m_text;
	sf::RectangleShape m_box;
};

class AnimatedTextBox {
public:
	AnimatedTextBox(sf::Font& font, unsigned int width, unsigned int height) :
		m_running(false),
		m_index(-1),
		m_cps(15),
		m_currentTime(0.0f) {

		m_box.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
		m_box.setFillColor(sf::Color::Transparent);
		m_box.setOutlineThickness(1.0f);

		m_text.setFont(font);
	}

	void setPosition(const sf::Vector2f& pos) {
		m_box.setPosition(pos);
		m_text.setPosition(pos);
	}

	void setText(const std::string& text, unsigned int fontSize, const sf::Color& color = sf::Color::Black) {
		m_string = text;

		m_text.setCharacterSize(fontSize);
		insertEOLCharacters(text);
		m_text.setFillColor(color);

		m_box.setOutlineColor(color);
	}

	void update(float dt) {
		if (m_running) {
			m_currentTime += dt;

			float updateTime = 1.0f / static_cast<float>(m_cps);

			if (m_currentTime >= updateTime) {
				m_currentTime = 0.0f;

				if (m_index < static_cast<int>(m_string.length())) m_index++;
			}
		}
	}

	void play() { m_running = true; }
	void stop() { m_running = false; }
	void reset() { 
		m_running = false;
		m_index = -1;
		m_currentTime = 0.0f;
	}

	void draw(sf::RenderWindow& window) {
		if (m_index == -1) return;

		m_text.setString(sf::String(m_string.substr(0, m_index)));

		window.draw(m_box);
		window.draw(m_text);
	}

protected:

	// Modifies the string to add end-of-line character when it goes beyond the box width

	// TODO: Optimize this so that we aren't creating so many strings...
	void insertEOLCharacters(std::string str) {
		m_string = "";

		std::stringstream ss(str);

		// Iterate through the words
		while (!ss.eof()) {
			std::string word;
			ss >> word;

			// Set a potential line equal to the current line plus a space and the current word
			std::string potential = m_string + " " + word;

			// Set the string in the text object to the potential line
			m_text.setString(potential);

			// If the potential line size is greater than the size of the box
			if (m_text.getLocalBounds().width >= m_box.getLocalBounds().width) {
				// Append an end-of-line character to the output string followed by the word
				m_string += "\n" + word;
			}
			else {
				// Handle the first word
				if (m_string.size() == 0) 
					m_string += word;
				// Append a space followed by the word to the output string
				else 
					m_string += " " + word;
			}
		}
	}

	float m_currentTime;
	bool m_running;
	int m_index;
	int m_cps;

	std::string m_string;
	sf::Text m_text;
	sf::RectangleShape m_box;
};

// TODO:
//		1. Replace m_string with a "string container"
//		2. m_string is replaced by a current string 
//		3. In the insert EOL characters method, when the local bounds of the text object extends beyond the
//			the height of the box, add the "current string" to the "string container"
//		4. When animating and the index hits the end of the current string being animated, reset the index 
//			and get the next string in the container
//		5. Allow for prompting of the user before continuing to the next string

const std::string loremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Message Box");

	sf::Font font;
	std::string fontFile = "../media/Fonts/arial.ttf";
	if (!font.loadFromFile(fontFile)) {
		std::cout << "Failed to load font " << fontFile << std::endl;
		return EXIT_FAILURE;
	}

	AnimatedTextBox textBox(font, 300, 200);
	textBox.setText(loremIpsum, 18, sf::Color::White);
	textBox.setPosition(sf::Vector2f(0.0f, 0.0f));

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
					textBox.play();
				}
				else if (event.key.code == sf::Keyboard::P) {
					textBox.stop();
				}
				else if (event.key.code == sf::Keyboard::R) {
					textBox.reset();
				}
			}
		}

		float updateTime = clock.getElapsedTime().asSeconds();
		textBox.update(elapsedTime);

		window.clear();
		textBox.draw(window);
		window.display();

		elapsedTime = clock.restart().asSeconds();
	}

	return EXIT_SUCCESS;
}