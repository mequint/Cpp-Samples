#pragma once

#include <string>
#include <unordered_map>

using AppSettings = std::unordered_map<std::string, std::string>;

// Loads application settings into am accessible data dictionary
class ConfigurationManager
{
	public:
		bool Load(std::string filename);

		std::string Get(std::string name) const;

	private:
		AppSettings m_appSettings;
};