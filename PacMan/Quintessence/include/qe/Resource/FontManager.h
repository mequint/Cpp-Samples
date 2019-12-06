#pragma once

#include <SFML/Graphics/Font.hpp>
#include "ResourceManager.h"
#include "qe/Utilities/Utilities.h"

namespace qe {
	class FontManager : public ResourceManager<FontManager, sf::Font> {
	public:
		bool load(sf::Font* resource, const std::string& path) {
			return resource->loadFromFile(Utils::getWorkingDirectory() + path);
		}
	};
}