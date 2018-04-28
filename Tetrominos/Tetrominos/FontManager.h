#pragma once

#include <map>
#include <string>
#include <vector>

#include "Font.h"

using Fonts = std::map<std::string, Font>;

class FontManager
{
	public:
		FontManager();
		~FontManager();

		Font& Load(const std::string& filename, const std::string& fontName, unsigned int fontSize);
		Font& GetFont(const std::string& fontName);

	private:
		Fonts m_fonts;	
};	