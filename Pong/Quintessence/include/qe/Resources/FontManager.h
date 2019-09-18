#pragma once

#include <SFML/Graphics/Font.hpp>
#include "ResourceManager.h"

namespace qe {
	class FontManager : public ResourceManager<FontManager, sf::Font> {
		public:
			bool Load(sf::Font* resource, const std::string& path);
	};
}