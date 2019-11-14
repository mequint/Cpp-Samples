#include "MessageBox.h"

MessageBox::MessageBox(sf::Font& font, unsigned int width, unsigned int height) {
	m_box.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(1.0f);

	m_text.setFont(font);
}

void MessageBox::setPosition(const sf::Vector2f& pos) {
	m_box.setPosition(pos);
	m_text.setPosition(pos);
}

void MessageBox::setText(const std::string& text, unsigned int fontSize, const sf::Color& color) {
	m_text.setString(text);
	m_text.setCharacterSize(fontSize);
	m_text.setFillColor(color);

	m_box.setOutlineColor(color);
}


void MessageBox::draw(sf::RenderWindow& window) {
	window.draw(m_box);
	window.draw(m_text);
}