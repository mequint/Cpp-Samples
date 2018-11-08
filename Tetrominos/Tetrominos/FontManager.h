#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>

class FontManager
{
	public:
		FontManager();
		~FontManager();

		bool LoadFont(const std::string& file, const std::string& id);
		sf::Font* GetFont(const std::string& id);

	private:
		std::unordered_map<std::string, sf::Font*> m_fonts;
};