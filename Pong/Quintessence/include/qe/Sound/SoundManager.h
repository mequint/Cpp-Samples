#pragma once

#include <memory>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>

#include "qe/Resources/AudioManager.h"
#include "qe/Sound/SoundProperties.h"

namespace qe {

	using SoundID = int;
	enum class StateType;

	struct SoundInfo {
		SoundInfo(const std::string& name) : 
			m_name(name), 
			m_manualPaused(false) {}

		std::string m_name;
		bool m_manualPaused;
	};

	using SoundPropertiesContainer = std::unordered_map<std::string, SoundProperties>;
	using SoundContainer = std::unordered_map<SoundID, std::pair<SoundInfo, std::unique_ptr<sf::Sound>>>;
	// using Sounds = std::unordered_map<StateType, SoundContainer>;	// Add this when we have separate states...
	using RecycledSounds = std::vector<std::pair<std::pair<SoundID, std::string>, std::unique_ptr<sf::Sound>>>;

	class SoundManager {
	public:
		SoundManager(AudioManager* audioManager);
		~SoundManager();

		void Update(float dt);

		SoundID Play(const std::string& soundName, bool loop = false, bool relative = false);

		bool Play(const SoundID& id);
		bool Stop(const SoundID& id);
		bool Pause(const SoundID& id);

		void AddSoundProperty(const std::string& name, float volume, float pitch, float minDistance, float attenuation);
		SoundProperties* GetSoundProperties(const std::string& name);

		static const int Max_Sounds = 128;
		static const int Sound_Cache = 64;

	private:
		bool CreateSound(SoundID& id, const std::string& audioName, std::unique_ptr<sf::Sound>& sound);
		void SetUpSound(sf::Sound* sound, const SoundProperties* props, bool loop, bool relative);

		void RecycleSound(const SoundID& id, std::unique_ptr<sf::Sound> sound, const std::string& name);

		SoundContainer m_sounds;
		SoundPropertiesContainer m_properties;
		RecycledSounds m_recycled;

		SoundID m_lastID;
		unsigned int m_numSounds;
		float m_elapsed;

		AudioManager* m_audioManager;
	};
}