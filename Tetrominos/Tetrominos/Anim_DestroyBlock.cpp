#include "Anim_DestroyBlock.h"

Anim_DestroyBlock::Anim_DestroyBlock(sf::RectangleShape& rectangle) :
	m_rectShape(rectangle),
	m_scaleTweener(1.0f, 1.2f, 30, 1.0 / 120.0f),
	m_alphaTweener(255, 0, 30, 1.0f / 120.0f),
	m_isComplete(false)
{
}

void Anim_DestroyBlock::Update(float dt)
{
	if (IsPlaying())
	{
		m_alphaTweener.Update(dt);
		m_scaleTweener.Update(dt);

		sf::Color fillColor = m_rectShape.getFillColor();
		sf::Color outlineColor = m_rectShape.getOutlineColor();
		
		fillColor.a = m_alphaTweener.CurrentStep();
		outlineColor.a = m_alphaTweener.CurrentStep();

		sf::Vector2f scale = sf::Vector2f(m_scaleTweener.CurrentStep(), m_scaleTweener.CurrentStep());

		m_rectShape.setFillColor(fillColor);
		m_rectShape.setOutlineColor(outlineColor);
		m_rectShape.setScale(scale);
	}
}

void Anim_DestroyBlock::Draw(sf::RenderWindow& window)
{
	window.draw(m_rectShape);
}

void Anim_DestroyBlock::Play()
{
	m_alphaTweener.Play();
	m_scaleTweener.Play();
}

bool Anim_DestroyBlock::IsPlaying()
{
	return m_alphaTweener.IsPlaying() && m_scaleTweener.IsPlaying();
}

bool Anim_DestroyBlock::IsComplete()
{
	return m_isComplete;
}