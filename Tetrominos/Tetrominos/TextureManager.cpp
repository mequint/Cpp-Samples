#include "TextureManager.h"

#include <GL/glew.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

Texture2D& TextureManager::LoadTexture(const std::string & filename, const std::string & name, bool gamma)
{
	sf::Image image;
	image.loadFromFile(filename);

	int width = image.getSize().x;
	int height = image.getSize().y;
	int internalFormat = gamma ? GL_SRGB_ALPHA : GL_RGBA;
	int imageFormat = GL_RGBA;
	const unsigned char* data = image.getPixelsPtr();

	Texture2D texture;
	texture.Init(data, width, height, internalFormat, imageFormat);

	m_textures[name] = texture;
	return m_textures[name];
}

Texture2D & TextureManager::GetTexture(const std::string & name)
{
	auto iter = m_textures.find(name);
	if (iter == m_textures.end())
	{
		std::cout << "<TextureManager>: Unable to find texture \'" << name << "\'" << std::endl;
		// TODO: throw an error...or something
	}

	return iter->second;
}