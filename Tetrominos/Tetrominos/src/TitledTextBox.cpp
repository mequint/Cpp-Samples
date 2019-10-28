#include "TitledTextBox.h"

TitledTextBox::TitledTextBox()
{
}

TitledTextBox::TitledTextBox(sf::Font & font, sf::Vector2f position, sf::Vector2f size, int textFontSize, std::string & title, int titleFontSize)
{
	m_rectangle.setPosition(position);
	m_rectangle.setSize(size);
	m_rectangle.setFillColor(sf::Color::Transparent);
	m_rectangle.setOutlineColor(sf::Color::White);
	m_rectangle.setOutlineThickness(-1.0f);

	m_title.setFont(font);
	m_title.setCharacterSize(titleFontSize);
	m_title.setString(title);
	m_title.setFillColor(sf::Color::White);

	m_text.setFont(font);
	m_text.setCharacterSize(textFontSize);
	m_text.setString("");
	m_text.setFillColor(sf::Color::White);

	sf::Vector2f rectTopCenter = sf::Vector2f(m_rectangle.getSize().x / 2.0f, 0.0f);
	sf::Vector2f titleCenter = sf::Vector2f(m_title.getLocalBounds().width / 2.0f, 0.0f);
	m_title.setPosition(position + rectTopCenter - titleCenter);
}

void TitledTextBox::SetText(const std::string & text)
{
	m_text.setString(text);

	sf::Vector2f position = m_rectangle.getPosition();
	sf::Vector2f rectCenter = m_rectangle.getSize() / 2.0f;
	sf::Vector2f textCenter = sf::Vector2f(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);

	m_text.setPosition(position + rectCenter - textCenter);
}

void TitledTextBox::Draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
	window.draw(m_title);
	window.draw(m_text);
}