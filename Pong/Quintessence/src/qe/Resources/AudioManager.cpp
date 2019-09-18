#include "qe/Resources/AudioManager.h"

#include "qe/Utilities/Utilities.h"

namespace qe {
	bool AudioManager::Load(sf::SoundBuffer* resource, const std::string& path) {
		return resource->loadFromFile(Utils::GetWorkingDirectory() + path);
	}
}