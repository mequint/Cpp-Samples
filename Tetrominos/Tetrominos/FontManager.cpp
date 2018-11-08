#include "FontManager.h"

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	while (m_fonts.begin() != m_fonts.end())
	{
		delete m_fonts.begin()->second;
		m_fonts.erase(m_fonts.begin());
	}
}

bool FontManager::LoadFont(const std::string& file, const std::string& id)
{
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(file)) return false;

	m_fonts.emplace(id, font);
	return true;
}

sf::Font* FontManager::GetFont(const std::string & id)
{
	auto iter = m_fonts.find(id);
	if (iter == m_fonts.end()) return nullptr;

	return iter->second;
}