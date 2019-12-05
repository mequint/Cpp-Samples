#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"
#include "qe/Utilities/Utilities.h"

namespace qe {
	class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
	public:
		bool load(sf::Texture* resource, const std::string& path) {
			return resource->loadFromFile(Utils::getWorkingDirectory() + path);
		}
	};
}