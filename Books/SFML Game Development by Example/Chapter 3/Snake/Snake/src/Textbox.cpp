#include "Textbox.h"

Textbox::Textbox() {
	Setup(5, 9, 200, sf::Vector2f(0.f, 0.0f));
}

Textbox::Textbox(int visible, int charSize, int width, const sf::Vector2f& screenPos) {
	Setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox() {
	Clear();
}

void Textbox::Setup(int visible, int charSize, int width, const sf::Vector2f& screenPos) {
	m_numVisible = visible;

	sf::Vector2f offset(2.0f, 2.0f);

	m_font.loadFromFile("arial.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(charSize);
	m_content.setFillColor(sf::Color::White);
	m_content.setPosition(screenPos + offset);

	m_backdrop.setSize(sf::Vector2f(static_cast<float>(width), (visible * (charSize * 1.2f))));
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	m_backdrop.setPosition(screenPos);
}

void Textbox::Add(const std::string & message) {
	m_messages.push_back(message);
	if (m_messages.size() < 6) return;

	m_messages.erase(m_messages.begin());
}

void Textbox::Clear() {
	m_messages.clear();
}

void Textbox::Render(sf::RenderWindow & window) {
	std::string content;
	for (auto& message : m_messages) {
		content.append(message + "\n");
	}

	if (content != "") {
		m_content.setString(content);
		window.draw(m_backdrop);
		window.draw(m_content);
	}
}