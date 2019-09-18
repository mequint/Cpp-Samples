#pragma once

#include <SFML/Graphics/Text.hpp>
#include <string>

#include "qe/Resources/FontManager.h"
#include "ECS/Components/Comp_Drawable.h"


class Comp_Text : public Comp_Drawable {
public:
	Comp_Text() : Comp_Drawable(Component::Text) {}
	~Comp_Text() = default;

	void Create(qe::FontManager* fontManager, const std::string& name) {
		if (fontManager->LoadResource(name)) {
			m_font = name;
			m_text.setFont(*fontManager->GetResource(m_font));
		}
	}

	sf::Vector2u GetSize() const {  
		auto bounds = m_text.getLocalBounds(); 
		return sf::Vector2u(static_cast<unsigned int>(bounds.width), static_cast<unsigned int>(bounds.height));
	}

	void Draw(sf::RenderWindow* window) {
		window->draw(m_text);
	}

	void SetPosition(const sf::Vector2f& position)	{ m_text.setPosition(position); }
	void SetText(const std::string& text) { m_text.setString(text); }
	void SetFontSize(unsigned int size) { m_text.setCharacterSize(size); }

private:
	std::string m_font;
	sf::Text m_text;
};