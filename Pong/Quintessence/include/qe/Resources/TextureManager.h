#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.h"

namespace qe {
	class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
	public:
		bool Load(sf::Texture* resource, const std::string& path);
	};
}