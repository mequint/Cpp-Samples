#include "AnimatedMessageBox.h"

#include <sstream>

AnimatedMessageBox::AnimatedMessageBox(sf::Font& font, unsigned int width, unsigned int height) :
	m_running(false),
	m_charIndex(-1),
	m_stringBlockIndex(0),
	m_cps(15),
	m_currentTime(0.0f),
	m_showPrompt(false),
	m_promptTime(0.0f) {

	m_box.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	m_box.setFillColor(sf::Color::Transparent);
	m_box.setOutlineThickness(1.0f);

	m_text.setFont(font);

}

void AnimatedMessageBox::setPosition(const sf::Vector2f& pos) {
	m_box.setPosition(pos);
	m_text.setPosition(pos);
	m_prompt.setPosition(m_box.getPosition().x + m_box.getSize().x - m_prompt.getSize().x, m_box.getPosition().y + m_box.getSize().y - m_prompt.getSize().y);
}

void AnimatedMessageBox::setText(const std::string& text, unsigned int charSize, const sf::Color& color) {
	m_text.setCharacterSize(charSize);
	_insertEOLCharacters(text);
	m_text.setFillColor(color);

	m_box.setOutlineColor(color);

	m_prompt.setSize(sf::Vector2f(static_cast<float>(charSize), static_cast<float>(charSize)));
	m_prompt.setPosition(m_box.getPosition().x + m_box.getSize().x - m_prompt.getSize().x, m_box.getPosition().y + m_box.getSize().y - m_prompt.getSize().y);
	m_prompt.setFillColor(color);
}

void AnimatedMessageBox::update(float dt) {
	if (m_running) {
		m_currentTime += dt;

		float updateTime = 1.0f / static_cast<float>(m_cps);

		if (m_currentTime >= updateTime) {
			m_currentTime = 0.0f;

			if (m_charIndex < static_cast<int>(m_stringContainer[m_stringBlockIndex].length())) m_charIndex++;
		}

		if (endOfBlock() && m_stringBlockIndex < static_cast<int>(m_stringContainer.size()) - 1) {
			m_showPrompt = true;
			m_promptTime += dt;

			if (m_promptTime >= 1.0f) {
				m_promptTime = 0.0f;
			}
			else if (m_promptTime >= 0.5f) {
				m_showPrompt = false;
			}
		}
	}
}

void AnimatedMessageBox::play() { m_running = true; }
void AnimatedMessageBox::stop() { m_running = false; }
void AnimatedMessageBox::reset() {
	m_running = false;
	m_charIndex = -1;
	m_stringBlockIndex = 0;
	m_currentTime = 0.0f;
}

void AnimatedMessageBox::skipAnimation() {
	m_charIndex = m_stringContainer[m_stringBlockIndex].length();
}

void AnimatedMessageBox::nextStringBlock() {
 	if (endOfBlock()) {
		if (m_stringBlockIndex < static_cast<int>(m_stringContainer.size() - 1)) {
			m_stringBlockIndex++;
			m_charIndex = -1;

			m_promptTime = 0.0f;
			m_showPrompt = false;
		}
	}
}

bool AnimatedMessageBox::isRunning() {
	return m_running;
}

bool AnimatedMessageBox::endOfBlock() {
	return m_charIndex == m_stringContainer[m_stringBlockIndex].length();
} 

void AnimatedMessageBox::draw(sf::RenderWindow& window) {
	if (m_charIndex == -1) return;

	m_text.setString(sf::String(m_stringContainer[m_stringBlockIndex].substr(0, m_charIndex)));

	window.draw(m_box);
	window.draw(m_text);

	if (m_showPrompt) {
		window.draw(m_prompt);
	}
}

void AnimatedMessageBox::setCharPerSeconds(int cps) { m_cps = cps; }

// TODO: Optimize this so that we aren't creating so many strings...
void AnimatedMessageBox::_insertEOLCharacters(const std::string& str) {
	std::string stringBlock = "";

	std::stringstream ss(str);

	// Iterate through the words
	while (!ss.eof()) {
		std::string word;
		ss >> word;

		m_text.setString(stringBlock + " " + word);

		if (m_text.getLocalBounds().width >= m_box.getLocalBounds().width) {
			m_text.setString(stringBlock + "\n" + word);
			if (m_text.getLocalBounds().height >= m_box.getLocalBounds().height) {
				m_stringContainer.emplace_back(stringBlock);
				stringBlock = word;
			}
			else {
				stringBlock += "\n" + word;
			}
		}
		else {
			if (stringBlock.size() == 0)
				stringBlock = word;
			else
				stringBlock += " " + word;
		}
	}

	// The last string block
	m_stringContainer.emplace_back(stringBlock);
}