#include "qe/Sound/SoundManager.h"

namespace qe {
	SoundManager::SoundManager(AudioManager * audioManager) :
		m_lastID(0),
		m_audioManager(audioManager),
		m_elapsed(0.0f),
		m_numSounds(0) {
	}

	SoundManager::~SoundManager() {
		for (auto& sound : m_sounds) {
			m_audioManager->ReleaseResource(sound.second.first.m_name);
		}

		for (auto& recycled : m_recycled) {
			m_audioManager->ReleaseResource(recycled.first.second);
		}

		m_recycled.clear();

		m_sounds.clear();

		m_properties.clear();

		m_lastID = 0;
		m_numSounds = 0;
	}

	void SoundManager::Update(float dt) {
		m_elapsed += dt;
		if (m_elapsed < 0.33f) return;

		m_elapsed = 0.0f;

		for (auto iter = m_sounds.begin(); iter != m_sounds.end();) {
			if (!iter->second.second->getStatus()) {
				RecycleSound(iter->first, std::move(iter->second.second), iter->second.first.m_name);
				iter = m_sounds.erase(iter);
				continue;
			}

			++iter;
		}

		--m_numSounds;
	}

	SoundID SoundManager::Play(const std::string & soundName, bool loop, bool relative) {
		auto props = GetSoundProperties(soundName);
		if (!props) return -1;

		SoundID id;
		std::unique_ptr<sf::Sound> sound;
		if (!CreateSound(id, props->m_audioName, sound)) return -1;

		SetUpSound(sound.get(), props, loop, relative);
		sound->play();

		SoundInfo info(props->m_audioName);
		m_sounds.emplace(id, std::make_pair(info, std::move(sound)));

		return id;
	}

	bool SoundManager::Play(const SoundID & id) {
		auto sound = m_sounds.find(id);
		if (sound == m_sounds.end()) return false;

		sound->second.second->play();
		sound->second.first.m_manualPaused = false;

		return true;
	}

	bool SoundManager::Stop(const SoundID & id) {
		auto sound = m_sounds.find(id);
		if (sound == m_sounds.end()) return false;

		sound->second.second->stop();
		sound->second.first.m_manualPaused = true;

		return true;
	}

	bool SoundManager::Pause(const SoundID & id) {
		auto sound = m_sounds.find(id);
		if (sound == m_sounds.end()) return false;

		sound->second.second->pause();
		sound->second.first.m_manualPaused = true;

		return true;
	}

	void SoundManager::AddSoundProperty(const std::string& name, float volume, float pitch, float minDistance, float attenuation) {
		SoundProperties props(name);
		props.m_volume = volume;
		props.m_pitch = pitch;
		props.m_minDistance = minDistance;
		props.m_attenuation = attenuation;

		m_properties.emplace(name, props);
	}

	SoundProperties* SoundManager::GetSoundProperties(const std::string & name) {
		auto properties = m_properties.find(name);
		if (properties == m_properties.end()) return nullptr;

		return &properties->second;
	}

	bool SoundManager::CreateSound(SoundID & id, const std::string & audioName, std::unique_ptr<sf::Sound>& sound) {
		if (m_numSounds < Max_Sounds) {
			if (m_audioManager->LoadResource(audioName)) {
				sound = std::make_unique<sf::Sound>();
				id = m_lastID;

				++m_lastID;
				++m_numSounds;

				sound->setBuffer(*m_audioManager->GetResource(audioName));
				return true;
			}
		}

		return false;
	}

	void SoundManager::SetUpSound(sf::Sound* sound, const SoundProperties* props, bool loop, bool relative) {
		sound->setVolume(props->m_volume);
		sound->setPitch(props->m_pitch);
		sound->setMinDistance(props->m_minDistance);
		sound->setAttenuation(props->m_attenuation);
		sound->setLoop(loop);
		sound->setRelativeToListener(relative);
	}

	void SoundManager::RecycleSound(const SoundID & id, std::unique_ptr<sf::Sound> sound, const std::string & name) {
		m_recycled.emplace_back(std::make_pair(id, name), std::move(sound));
	}
}