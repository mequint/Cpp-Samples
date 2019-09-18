#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.h"

namespace qe {
	class AudioManager : public ResourceManager<AudioManager, sf::SoundBuffer> {
	public:
		bool Load(sf::SoundBuffer* resource, const std::string& path);
	};
}