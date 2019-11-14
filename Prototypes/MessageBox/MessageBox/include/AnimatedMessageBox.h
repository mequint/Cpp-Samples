#pragma once

#include <SFML/Graphics.hpp>

class AnimatedMessageBox {
public:
	AnimatedMessageBox(sf::Font& font, unsigned int width, unsigned int height);

	void setPosition(const sf::Vector2f& pos);
	void setText(const std::string& text, unsigned int charSize, const sf::Color& color = sf::Color::Black);

	void update(float dt);

	void play();
	void stop();
	void reset();

	void skipAnimation();
	void nextStringBlock();

	bool isRunning();
	bool endOfBlock();

	void draw(sf::RenderWindow& window);

	void setCharPerSeconds(int cps);

private:

	void _insertEOLCharacters(const std::string& str);

	int m_cps;

	bool m_running;
	float m_currentTime;

	sf::Text m_text;
	sf::RectangleShape m_box;

	sf::RectangleShape m_prompt;
	bool m_showPrompt;
	float m_promptTime;

	std::vector<std::string> m_stringContainer;
	int m_stringBlockIndex;
	int m_charIndex;
};