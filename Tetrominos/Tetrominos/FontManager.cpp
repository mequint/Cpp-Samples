#include "FontManager.h"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::Load(const std::string& filename, const std::string& fontName, unsigned int fontSize)
{
	if (isFontLoaded(fontName, fontSize)) return;

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "<FontManager>: Could not initialize FreeType library" << std::endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, filename.c_str(), 0, &face))
	{
		std::cout << "<FontManager>: Failed to load font " << fontName << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Font font;
	for (unsigned char c = 0; c < 128; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "<FontManager>: Failed to load FreeType Glyph" << std::endl;
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Glyph glyph =
		{
			texture,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x
		};

		font.m_glyphs.insert(std::pair<unsigned char, Glyph>(c, glyph));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	m_fonts[fontName] = font;
	m_loadedFonts.emplace_back(fontName, fontSize);
}

Font& FontManager::GetFont(const std::string & fontName)
{
	auto iter = m_fonts.find(fontName);
	if (iter == m_fonts.end())
	{
		std::cout << "<FontManager>: Could not find font " << fontName << std::endl;
		// Should throw an error...or something...
	}

	return iter->second;
}

bool FontManager::isFontLoaded(const std::string & fontName, unsigned int fontSize)
{
	for (auto font : m_loadedFonts)
	{
		if (font.first == fontName && font.second == fontSize) return true;
	}

	return false;
}
