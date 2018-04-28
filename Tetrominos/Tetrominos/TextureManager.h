#pragma once

#include <unordered_map>

#include "Texture.h"

using Textures = std::unordered_map<std::string, Texture2D>;

class TextureManager
{
	public:
		TextureManager();
		~TextureManager();

		Texture2D& LoadTexture(const std::string& filename, const std::string& name, bool gamma = false);
		Texture2D& GetTexture(const std::string& name);

	private:
		Textures m_textures;
};