#pragma once

#include <SFML/Graphics.hpp>

class TitledTextBox
{
	public:
		TitledTextBox();
		TitledTextBox(sf::Font& font, sf::Vector2f position, sf::Vector2f size, int textFontSize, std::string& title, int titleFontSize);

		void SetText(const std::string& text);

		void Draw(sf::RenderWindow& window);

	private:
		sf::RectangleShape m_rectangle;
		sf::Text m_title;
		sf::Text m_text;
};