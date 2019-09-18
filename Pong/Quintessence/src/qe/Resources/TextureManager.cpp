#include "qe/Resources/TextureManager.h"

#include "qe/Utilities/Utilities.h"

namespace qe {
	bool TextureManager::Load(sf::Texture* resource, const std::string& path) {
		return resource->loadFromFile(Utils::GetWorkingDirectory() + path);
	}
}