#include "Views/ProgressBarView.h"

ProgressBarView::ProgressBarView() : 
	m_currentValue(100), 
	m_maxValue(100), 
	m_isMirrored(false),
	m_progressColor(sf::Color::Red),
	m_emptyColor(sf::Color::White) {
}

ProgressBarView::~ProgressBarView() = default;

void ProgressBarView::Draw(sf::RenderWindow * window) {	
	// Use the current value and the max value to determine the percentage of the bar
	float percentage = static_cast<float>(m_currentValue) / static_cast<float>(m_maxValue);

	float leftSideWidth = percentage * m_barRect.width;
	// Figure out the length of the bar on the left using the width of the bar rect property
	sf::RectangleShape leftSide;
	leftSide.setPosition(m_barRect.left, m_barRect.top);
	leftSide.setSize(sf::Vector2f(leftSideWidth, m_barRect.height));
	leftSide.setFillColor(m_progressColor);

	// Figure out the length of the bar on the right using the remainder of the bar rect
	sf::RectangleShape rightSide;
	rightSide.setPosition(m_barRect.left + leftSideWidth, m_barRect.top);
	rightSide.setSize(sf::Vector2f(m_barRect.height, m_barRect.width - leftSideWidth));
	rightSide.setFillColor(m_emptyColor);

	window->draw(leftSide);
	window->draw(rightSide);
}

void ProgressBarView::SetCurrentValue(int value) {
	if (value < 0) {
		m_currentValue = 0;
	}
	else if (value > m_maxValue) {
		m_currentValue = m_maxValue;
	}
	else {
		m_currentValue = value;
	}
}

void ProgressBarView::SetMaxValue(int value) {
	if (m_maxValue < 0) {
		m_maxValue = 0;
	} 
	else {
		m_maxValue = value;
	}
}

void ProgressBarView::SetMirrored(bool mirrored) {
	m_isMirrored = mirrored;
}

void ProgressBarView::SetProgressColor(const sf::Color& color) {
	m_progressColor = color;
}

void ProgressBarView::SetEmptyColor(const sf::Color& color) {
	m_emptyColor = color;
}

void ProgressBarView::SetPosition(const sf::Vector2f & position) {
	m_barRect.left = position.x;
	m_barRect.top = position.y;
}

void ProgressBarView::SetBarSize(float width, float height) {
	if (width < 0.0f || height < 0.0f) return;

	m_barRect.width = width;
	m_barRect.height = height;
}

float ProgressBarView::GetWidth() const {
	return m_barRect.width;
}

float ProgressBarView::GetHeight() const {
	return m_barRect.height;
}