#include "Anim_Directional.h"

#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"

void Anim_Directional::FrameStep() {
	bool b = SetFrame(m_frameCurrent + (m_frameStart <= m_frameEnd ? 1 : -1));
	if (b) return;

	if (m_loop) {
		SetFrame(m_frameStart);
	}
	else {
		SetFrame(m_frameEnd);
		Pause();
	}
}

void Anim_Directional::CropSprite() {
	sf::Vector2f padding = m_spriteSheet->GetSheetPadding();
	sf::Vector2f spacing = m_spriteSheet->GetSpriteSpacing();

	sf::IntRect rect(
		static_cast<int>((m_spriteSheet->GetSpriteSize().x * m_frameCurrent) + padding.x + (spacing.x * m_frameCurrent)),
		static_cast<int>((m_spriteSheet->GetSpriteSize().y * (m_frameRow + static_cast<unsigned int>(m_spriteSheet->GetDirection())) 
		+ padding.y + (m_frameRow + static_cast<unsigned int>(m_spriteSheet->GetDirection())) * spacing.y)),
		m_spriteSheet->GetSpriteSize().x, m_spriteSheet->GetSpriteSize().y);
	m_spriteSheet->CropSprite(rect);
}

void Anim_Directional::ReadIn(std::stringstream& stream) {
	stream >> m_frameStart >> m_frameEnd >> m_frameRow >> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}