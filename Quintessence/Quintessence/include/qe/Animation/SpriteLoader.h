#pragma once

#include <memory>
#include "qe/Animation/SpriteAnimation.h"
#include "qe/Resource/TextureManager.h"

namespace qe {
	class SpriteLoader {
		friend class SpriteAnimation;
		friend class AnimationController;

	public:
		SpriteLoader(TextureManager* textureManager);
		
		std::unique_ptr<SpriteAnimation> loadFromJsonFile(const std::string& filepath);

	private:
		TextureManager* m_textureManager;
	};
}