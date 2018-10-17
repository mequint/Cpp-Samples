#pragma once

#include <SFML/Graphics.hpp>

class TextBox
{
	public:
		TextBox();
		TextBox(sf::Font& font, int fontSize);

		void SetPosition(sf::Vector2f position);
		void SetText(const std::string& text);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Text m_text;
};