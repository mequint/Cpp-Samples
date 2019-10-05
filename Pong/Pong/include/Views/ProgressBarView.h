#pragma once

#include <SFML/Graphics.hpp>

class ProgressBarView {
public:
	ProgressBarView();
	~ProgressBarView();

	void Draw(sf::RenderWindow* window);
	
	void SetCurrentValue(int value);
	void SetMaxValue(int value);
	
	void SetProgressColor(const sf::Color& color);
	void SetEmptyColor(const sf::Color& color);

	void SetPosition(const sf::Vector2f& position);
	void SetBarSize(float width, float height);
	float GetWidth() const;
	float GetHeight() const;

private:
	sf::FloatRect m_barRect;

	sf::Color m_progressColor;
	sf::Color m_emptyColor;

	int m_currentValue;
	int m_maxValue;
};