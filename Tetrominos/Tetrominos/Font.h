#pragma once

#include <map>

#include "Texture.h"

struct Glyph
{
	unsigned int TextureID;
	int Width, Height;
	int BearingX, BearingY;
	unsigned int Advance;
};

using Glyphs = std::map<unsigned char, Glyph>;

class Font
{
	friend class FontManager;

	public:
		Glyph GetGlyph(unsigned char character);

	private:
		Glyphs m_glyphs;
};