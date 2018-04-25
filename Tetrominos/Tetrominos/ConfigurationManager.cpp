#include "ConfigurationManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

bool ConfigurationManager::Load(std::string filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "<ConfigurationManager>: Failed to open file " << filename << std::endl;
		return false;
	}
	else
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string name, value;

			ss >> name;
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			
			value = line.substr(name.length());
			
			// Trim the white space from the front...
			size_t lastTab = value.find_last_of('\t');
			value = value.substr(lastTab + 1);
			
			m_appSettings[name] = value;
		}
	}

	return true;
}

std::string ConfigurationManager::Get(std::string name) const
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	auto iter = m_appSettings.find(name);
	if (iter == m_appSettings.end())
	{
		std::cout << "<ConfigurationManager>: Unable to find key " << name << std::endl;
		return std::string();		// Should throw an error but an empty string will do...
	}

	return iter->second;
}