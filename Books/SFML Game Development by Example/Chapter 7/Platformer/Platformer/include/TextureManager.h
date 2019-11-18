#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.h"

class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
public:
	TextureManager() : ResourceManager("textures.cfg") {}

	sf::Texture* Load(const std::string& path) {
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(Utils::GetWorkingDirectory() + path)) {
			delete texture;
			texture = nullptr;
			std::cerr << "! Failed to load texture: " << path << std::endl;
		}

		return texture;
	}
};