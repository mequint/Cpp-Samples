#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"
#include "qe/Utilities/Utilities.h"

namespace qe {
	class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
	public:
		bool load(sf::Texture* resource, const std::string& path) {
			auto loadedSuccessfully = false;

			// Load from file
			if (resource->loadFromFile(Utils::getWorkingDirectory() + path)) {
				loadedSuccessfully = true;
			}

			// TODO: Set the resource to a "null texture"

			return loadedSuccessfully;
		}
	};
}