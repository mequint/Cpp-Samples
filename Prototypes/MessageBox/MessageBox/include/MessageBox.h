#pragma once

#include <SFML/Graphics.hpp>

class MessageBox {
public:
	MessageBox(sf::Font& font, unsigned int width, unsigned int height);

	void setPosition(const sf::Vector2f& pos);
	void setText(const std::string& text, unsigned int charSize, const sf::Color& color = sf::Color::Black);
	
	void draw(sf::RenderWindow& window);

private:
	sf::Text m_text;
	sf::RectangleShape m_box;
};