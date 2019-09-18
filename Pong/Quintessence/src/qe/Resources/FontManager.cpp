#include "qe/Resources/FontManager.h"

#include "qe/Utilities/Utilities.h"

namespace qe {
	bool FontManager::Load(sf::Font* resource, const std::string& path) {
		return resource->loadFromFile(Utils::GetWorkingDirectory() + path);
	}
}