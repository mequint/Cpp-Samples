#pragma once

#include <SFML/Graphics/Font.hpp>
#include "ResourceManager.h"

class FontManager : public ResourceManager<FontManager, sf::Font> {
public:
	FontManager() : ResourceManager("fonts.cfg") {}

	sf::Font* Load(const std::string& path) {
		sf::Font* font = new sf::Font();
		if (!font->loadFromFile(Utils::GetWorkingDirectory() + path)) {
			delete font;
			font = nullptr;
			std::cout << "! Failed to load font: " << path << std::endl;
		}

		return font;
	}
};