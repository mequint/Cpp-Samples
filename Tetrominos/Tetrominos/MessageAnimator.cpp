#include "MessageAnimator.h"

#include <iostream>

MessageAnimator::MessageAnimator(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight),
	m_scaleTweener(0.2f, 1.0f, 30, 1.0f / 60.0f), m_alphaTweener(0.2f, 1.0f, 30, 1.0f / 60.0f), m_waitTweener(0.0f, 0.0f, 15, 1.0f / 60.0f)
{
	m_font.loadFromFile("arial.ttf");
}

void MessageAnimator::AddMessage(std::string & message)
{
	m_messages.push(message);
}

void MessageAnimator::Update(float dt)
{
	if (!m_messages.empty())
	{
		if (m_scaleTweener.IsPlaying() && m_alphaTweener.IsPlaying())
		{
			m_scaleTweener.Update(dt);
			m_alphaTweener.Update(dt);

			if (m_scaleTweener.IsComplete() && m_alphaTweener.IsComplete())
			{
				m_waitTweener.Play();
			}
		}

		if (m_waitTweener.IsPlaying())
		{
			m_waitTweener.Update(dt);

			if (m_waitTweener.IsComplete())
			{
				m_scaleTweener.Reset();
				m_alphaTweener.Reset();
				m_waitTweener.Reset();
				m_messages.pop();

				if (!m_messages.empty())
				{
					Start();
				}
			}
		}
	}
}

void MessageAnimator::Draw(sf::RenderWindow& window)
{
	if (!m_messages.empty())
	{
		sf::Text text;
		text.setFillColor(sf::Color::White);
		text.setFont(m_font);
		text.setCharacterSize(32);
		text.setString(m_messages.front());
		text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
		text.setPosition((float)m_screenWidth / 2.0f, (float)m_screenHeight / 2.0f);

		float scale = m_scaleTweener.CurrentStep();
		text.setScale(sf::Vector2f(scale, scale));

		sf::Color textColor = text.getFillColor();
		textColor.a = (float)textColor.a * m_alphaTweener.CurrentStep();
		text.setFillColor(textColor);
		window.draw(text);
	}
}

void MessageAnimator::Start()
{
	m_scaleTweener.Play();
	m_alphaTweener.Play();
}

bool MessageAnimator::IsAnimationComplete()
{
	return !m_alphaTweener.IsPlaying() && !m_scaleTweener.IsPlaying() && !m_waitTweener.IsPlaying();
}