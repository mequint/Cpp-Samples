#include "SoundManager.h"

SoundManager::SoundManager(AudioManager * audioManager) :
	m_lastID(0), 
	m_audioManager(audioManager),
	m_elapsed(0.0f),
	m_numSounds(0) {}

SoundManager::~SoundManager() {
	Cleanup();
}

void SoundManager::ChangeState(const StateType & state) {
	PauseAll(m_currentState);
	UnpauseAll(state);
	m_currentState = state;

	if (m_music.find(m_currentState) != m_music.end()) return;

	SoundInfo info("");
	sf::Music* music = nullptr;
	m_music.emplace(m_currentState, std::make_pair(info, music));
}

void SoundManager::RemoveState(const StateType & state) {
	auto& stateSounds = m_audio.find(state)->second;
	for (auto& iter : stateSounds) {
		RecycleSound(iter.first, iter.second.second, iter.second.first.m_name);
	}

	m_audio.erase(state);
	
	auto music = m_music.find(state);
	if (music == m_music.end()) return;

	if (music->second.second) {
		delete music->second.second;
		--m_numSounds;
	}

	m_music.erase(state);
}

void SoundManager::Update(float dt) {
	m_elapsed += dt;
	if (m_elapsed < 0.33f) return;

	m_elapsed = 0;
	auto& container = m_audio[m_currentState];

	for (auto iter = container.begin(); iter != container.end(); ) {
		if (!iter->second.second->getStatus()) {
			RecycleSound(iter->first, iter->second.second, iter->second.first.m_name);
			iter = container.erase(iter);
			continue;
		}

		++iter;
	}

	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) return;
	if (!music->second.second) return;
	if (music->second.second->getStatus()) return;

	delete music->second.second;
	music->second.second = nullptr;

	--m_numSounds;
}

SoundID SoundManager::Play(const std::string & sound, const sf::Vector3f & position, bool loop, bool relative) {
	SoundProps* props = GetSoundProperties(sound);
	if (!props) return -1;

	SoundID id;
	sf::Sound* snd = CreateSound(id, props->m_audioName);
	if (!snd) return -1;

	SetUpSound(snd, props, loop, relative);
	snd->setPosition(position);

	SoundInfo info(props->m_audioName);
	m_audio[m_currentState].emplace(id, std::make_pair(info, snd));
	snd->play();

	return id;
}

bool SoundManager::Play(const SoundID & id) {
	auto& container = m_audio[m_currentState];

	auto sound = container.find(id);
	if (sound == container.end()) return false;

	sound->second.second->play();
	sound->second.first.m_manualPaused = false;

	return true;
}

bool SoundManager::Stop(const SoundID & id) {
	auto& container = m_audio[m_currentState];
	
	auto sound = container.find(id);
	if (sound == container.end()) return false;

	sound->second.second->stop();
	sound->second.first.m_manualPaused = true;

	return true;
}

bool SoundManager::Pause(const SoundID & id) {
	auto& container = m_audio[m_currentState];
	
	auto sound = container.find(id);
	if (sound == container.end()) return false;

	sound->second.second->pause();
	sound->second.first.m_manualPaused = true;

	return true;
}

bool SoundManager::PlayMusic(const std::string & musicId, float volume, bool loop) {
	auto s = m_music.find(m_currentState);
	if (s == m_music.end()) return false;

	std::string path = m_audioManager->GetPath(musicId);
	if (path == "") return false;

	if (!s->second.second) {
		s->second.second = new sf::Music();
		++m_numSounds;
	}

	sf::Music* music = s->second.second;
	if (!music->openFromFile(Utils::GetWorkingDirectory() + path)) {
		delete music;
		--m_numSounds;
		s->second.second = nullptr;

		std::cerr << "[SoundManager] Failed to load music from file: " << musicId << std::endl;
		return false;
	}

	music->setLoop(loop);
	music->setVolume(volume);
	music->setRelativeToListener(true);
	music->play();

	s->second.first.m_name = musicId;

	return true;
}

bool SoundManager::PlayMusic(const StateType & state) {
	auto music = m_music.find(m_currentState);

	if (music == m_music.end()) return false;
	if (!music->second.second) return false;

	music->second.second->play();
	music->second.first.m_manualPaused = false;

	return true;
}

bool SoundManager::StopMusic(const StateType & state) {
	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) return false;
	if (!music->second.second) return false;

	music->second.second->stop();
	delete music->second.second;
	music->second.second = nullptr;

	--m_numSounds;

	return true;
}

bool SoundManager::PauseMusic(const StateType & state) {
	auto music = m_music.find(m_currentState);
	if (music == m_music.end()) return false;
	if (!music->second.second) return false;

	music->second.second->pause();
	music->second.first.m_manualPaused = true;

	return true;
}

bool SoundManager::SetPosition(const SoundID & id, const sf::Vector3f & pos) {
	auto& container = m_audio[m_currentState];
	
	auto sound = container.find(id);
	if (sound == container.end()) return false;

	sound->second.second->setPosition(pos);
	return true;
}

bool SoundManager::IsPlaying(const SoundID & id) {
auto& container = m_audio[m_currentState];
auto sound = container.find(id);

return (sound != container.end() ? sound->second.second->getStatus() : false);
}

SoundProps* SoundManager::GetSoundProperties(const std::string& soundName) {
	auto properties = m_properties.find(soundName);
	if (properties == m_properties.end()) {
		if (!LoadProperties(soundName)) return nullptr;
		properties = m_properties.find(soundName);
	}

	return &properties->second;
}

bool SoundManager::LoadProperties(const std::string & filename) {
	std::ifstream file;

	file.open(Utils::GetWorkingDirectory() + "media/Sounds/" + filename + ".sound");
	if (!file.is_open()) {
		std::cerr << "Failed to load sound: " << filename << std::endl;
		return false;
	}

	SoundProps props("");
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "Audio") {
			keystream >> props.m_audioName;
		}
		else if (type == "Volume") {
			keystream >> props.m_volume;
		}
		else if (type == "Pitch") {
			keystream >> props.m_pitch;
		}
		else if (type == "Distance") {
			keystream >> props.m_minDistance;
		}
		else if (type == "Attenuation") {
			keystream >> props.m_attenuation;
		}
		else {
			// ?
		}
	}

	file.close();

	if (props.m_audioName == "") return false;

	m_properties.emplace(filename, props);
	return true;
}

void SoundManager::PauseAll(const StateType & state) {
	auto& container = m_audio[state];
	for (auto iter = container.begin(); iter != container.end();) {
		if (!iter->second.second->getStatus()) {
			RecycleSound(iter->first, iter->second.second, iter->second.first.m_name);
			iter = container.erase(iter);
			continue;
		}

		iter->second.second->pause();
		++iter;
	}

	auto music = m_music.find(state);
	if (music == m_music.end()) return;
	if (!music->second.second) return;

	music->second.second->pause();
}

void SoundManager::UnpauseAll(const StateType & state) {
	auto& container = m_audio[state];

	for (auto& iter : container) {
		if (iter.second.first.m_manualPaused) continue;
		iter.second.second->play();
	}

	auto music = m_music.find(state);
	if (music == m_music.end()) return;

	if (!music->second.second || music->second.first.m_manualPaused) return;

	music->second.second->play();
}

sf::Sound * SoundManager::CreateSound(SoundID & id, const std::string & audioName) {
	sf::Sound* sound = nullptr;
	if (!m_recycled.empty() && (m_numSounds >= Max_Sounds || m_recycled.size() >= Sound_Cache)) {
		auto iter = m_recycled.begin();
		while (iter != m_recycled.end()) {
			if (iter->first.second == audioName) break;
			++iter;
		}

		if (iter == m_recycled.end()) {
			auto element = m_recycled.begin();

			id = element->first.first;
			
			m_audioManager->ReleaseResource(element->first.second);
			m_audioManager->RequireResource(audioName);

			sound = element->second;
			sound->setBuffer(*m_audioManager->GetResource(audioName));

			m_recycled.erase(element);
		}
		else {
			id = iter->first.first;
			sound = iter->second;
			m_recycled.erase(iter);
		}

		return sound;
	}

	if (m_numSounds < Max_Sounds) {
		if (m_audioManager->RequireResource(audioName)) {
			sound = new sf::Sound();
			id = m_lastID;

			++m_lastID;
			++m_numSounds;

			sound->setBuffer(*m_audioManager->GetResource(audioName));

			return sound;
		}
	}

	std::cerr << "[SoundManager] Failed to create sound." << std::endl;
	return nullptr;
}

void SoundManager::SetUpSound(sf::Sound * snd, const SoundProps * props, bool loop, bool relative) {
	snd->setVolume(props->m_volume);
	snd->setPitch(props->m_pitch);
	snd->setMinDistance(props->m_minDistance);
	snd->setAttenuation(props->m_attenuation);
	snd->setLoop(loop);
	snd->setRelativeToListener(relative);
}

void SoundManager::RecycleSound(const SoundID & id, sf::Sound * snd, const std::string & name) {
	m_recycled.emplace_back(std::make_pair(id, name), snd);
}

void SoundManager::Cleanup() {
	for (auto& state : m_audio) {
		for (auto& sound : state.second) {
			m_audioManager->ReleaseResource(sound.second.first.m_name);
			delete sound.second.second;
		}
	}

	m_audio.clear();

	for (auto& recycled : m_recycled) {
		m_audioManager->ReleaseResource(recycled.first.second);
		delete recycled.second;
	}
	m_music.clear();

	m_properties.clear();
	m_numSounds = 0;
	m_lastID = 0;
}