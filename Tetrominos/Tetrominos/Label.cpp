#include "Label.h"

Label::Label() {}

Label::Label(sf::Font& font, int fontSize)
{
	m_text.setFont(font);
	m_text.setCharacterSize(fontSize);
	m_text.setString("");
	m_text.setFillColor(sf::Color::White);
}

void Label::SetPosition(sf::Vector2f position)
{
	m_text.setPosition(position);
}

void Label::SetText(const std::string & text)
{
	if (m_text.getString() == text) return;

	m_text.setString(text);
}

void Label::Draw(sf::RenderWindow & window)
{
	window.draw(m_text);
}
