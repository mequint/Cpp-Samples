#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

#include "qe/Animation/AnimationControl.h"
#include "qe/Resource/TextureManager.h"

namespace qe {
	using Animations = std::unordered_map<std::string, std::unique_ptr<AnimationControl>>;

	class SpriteAnimation {
	public:
		SpriteAnimation(TextureManager* textureManager);
		~SpriteAnimation();

		void setTexture(const std::string& textureName);
		void setFrameSize(unsigned int width, unsigned int height);
		void setPosition(const sf::Vector2f& position);
		void setPosition(float x, float y);

		bool addAnimation(std::unique_ptr<AnimationControl> animation);

		AnimationControl* getCurrentAnimation();
		bool changeAnimation(const std::string& action, bool play = false);

		void update(float dt);
		void draw(sf::RenderTarget* target);

	private:
		Animations m_animations;
		AnimationControl* m_currentAnimation;

		std::string m_textureName;
		sf::Sprite m_sprite;
		sf::Vector2u m_frameSize;

		TextureManager* m_textureManager;
	};
}