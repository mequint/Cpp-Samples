#include "TextureManager.h"

#include <iostream>
#include <string>

#include "StbImage.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

Texture2D& TextureManager::LoadTexture(const std::string & filename, const std::string & name, bool gamma)
{
	int width, height, nrComponents;
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	int internalFormat, imageFormat;
	// Set formats
	if (nrComponents == 1)
	{
		internalFormat = imageFormat = GL_RED;
	}
	else if (nrComponents == 3)
 	{
		internalFormat = gamma ? GL_SRGB : GL_RGB;
		imageFormat = GL_RGB;
	}
	else if (nrComponents == 4)
	{
		internalFormat = gamma ? GL_SRGB_ALPHA : GL_RGBA;
		imageFormat = GL_RGBA;
	}

	Texture2D texture;
	texture.Init(image, width, height, internalFormat, imageFormat);

	m_textures[name] = texture;
	return m_textures[name];
}

Texture2D & TextureManager::GetTexture(const std::string & name)
{
	auto iter = m_textures.find(name);
	if (iter == m_textures.end())
	{
		std::cout << "<TextureManager>: Unable to find shader \'" << name << "\'" << std::endl;
		// TODO: throw an error...or something
	}

	return iter->second;
}