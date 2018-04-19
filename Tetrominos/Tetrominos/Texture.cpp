#include "Texture.h"

#include <glad/glad.h>

Texture2D::Texture2D() 
{
	glGenTextures(GL_TEXTURE_2D, &m_ID);
}

void Texture2D::Init(unsigned char* data, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int imageFormat)
{
	m_width = width;
	m_height = height;

	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
