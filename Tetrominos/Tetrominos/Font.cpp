#include "Font.h"

Glyph Font::GetGlyph(unsigned char character)
{
	return m_glyphs[character];
}