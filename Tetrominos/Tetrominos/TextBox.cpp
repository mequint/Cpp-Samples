#include "TextBox.h"

TextBox::TextBox() {}

TextBox::TextBox(sf::Font& font, int fontSize)
{
	m_text.setFont(font);
	m_text.setCharacterSize(fontSize);
	m_text.setString("");
	m_text.setFillColor(sf::Color::White);
}

void TextBox::SetPosition(sf::Vector2f position)
{
	m_text.setPosition(position);
}

void TextBox::SetText(const std::string & text)
{
	if (m_text.getString() == text) return;

	m_text.setString(text);
}

void TextBox::Draw(sf::RenderWindow & window)
{
	window.draw(m_text);
}
