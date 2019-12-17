#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Drawable.h"

#include "qe/Resource/TextureManager.h"

enum class Origin { UpRight, Center };

class C_Sprite : public C_Drawable {
public:
	C_Sprite() : C_Drawable(Component::Sprite) {}
	~C_Sprite() = default;

	void create(qe::TextureManager* textureManager, const std::string& name) {
		if (textureManager->loadResource(name)) {
			m_textureName = name;
			m_sprite.setTexture(*textureManager->getResource(m_textureName));
		}
	}

	void setOrigin(const Origin& origin) {
		if (m_textureName == "") return;

		switch (origin) {
			case Origin::UpRight: {
				m_sprite.setOrigin(0.0f, 0.0f);

				break;
			}

			case Origin::Center: {
				auto size = m_sprite.getTexture()->getSize();
				m_sprite.setOrigin(static_cast<float>(size.x / 2), static_cast<float>(size.y / 2));

				break;
			}
		}
	}

	// Inherited via C_Drawable
	virtual void setPosition(const sf::Vector2f & vector) override {
		m_sprite.setPosition(vector);
	}

	virtual void draw(sf::RenderTarget * target) override {
		target->draw(m_sprite);
	}

private:
	sf::Sprite m_sprite;
	std::string m_textureName;
};