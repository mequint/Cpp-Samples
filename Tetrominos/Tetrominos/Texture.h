#pragma once

class Texture2D
{
	friend class TextureManager;

	public:
		Texture2D();

		void Init(const unsigned char* data, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int imageFormat);
		void Bind() const;

	private:
		unsigned int m_ID;
		int m_width, m_height;
		int m_internalFormat;
		int m_imageFormat;
};