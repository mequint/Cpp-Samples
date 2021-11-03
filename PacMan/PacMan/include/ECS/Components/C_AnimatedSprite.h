#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Drawable.h"

#include "qe/Animation/SpriteAnimation.h"
#include "qe/Animation/SpriteLoader.h"
#include "qe/Resource/TextureManager.h"

#include "qe/Utilities/Utilities.h"

class C_AnimatedSprite : public C_Drawable {
public:
	C_AnimatedSprite() : C_Drawable(Component::AnimatedSprite), m_sprite(nullptr) {}
	~C_AnimatedSprite() = default;

	void create(qe::TextureManager* textureManager, const std::string& name) {
		if (m_sprite) return;

		if (textureManager->loadResource(name)) {

			m_textureName = name;

			qe::SpriteLoader loader(textureManager);
			m_sprite = loader.loadFromJsonFile("../media/animations/" + name + ".json");
		}
	}

	qe::SpriteAnimation* getSprite() { return m_sprite.get(); }

	// Inherited from C_Drawable
	virtual sf::Vector2u getSize() const override { 
		return m_sprite->getFrameSize(); 
	}

	virtual sf::Vector2f getPosition() const override { 
		return m_sprite->getPosition(); 
	}
	
	virtual void setPosition(const sf::Vector2f& vector) {
		m_sprite->setPosition(vector);
	}

	virtual void draw(sf::RenderTarget* target) override {
		if (!m_sprite) return;

		m_sprite->draw(target);
	}

private:
	std::unique_ptr<qe::SpriteAnimation> m_sprite;
	std::string m_textureName;
};