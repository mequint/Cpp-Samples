#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include "qe/ECS/ECS_Types.h"
#include "qe/Resources/TextureManager.h"

#include "ECS/Components/Comp_Drawable.h"

class Comp_Sprite : public Comp_Drawable {
public:
	Comp_Sprite() : Comp_Drawable(Component::Sprite) {}
	~Comp_Sprite() = default;

	void Create(qe::TextureManager* textureManager, const std::string& name) {
		// Load the texture
		if (textureManager->LoadResource(name)) {
			// Store the sprite size
			m_texture = name;
			m_sprite.setTexture(*textureManager->GetResource(m_texture));
		}
	}

	void Draw(sf::RenderWindow* window) {
		window->draw(m_sprite);
	}

	sf::Vector2u GetSize() const {
		return sf::Vector2u(static_cast<unsigned int>(m_sprite.getLocalBounds().width), 
			static_cast<unsigned int>(m_sprite.getLocalBounds().height));
	}

	void SetPosition(const sf::Vector2f& vector) {
		m_sprite.setPosition(vector);
	}

private:
	std::string m_texture;
	sf::Sprite m_sprite;
};