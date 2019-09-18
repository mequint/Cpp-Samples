#pragma once

#include <array>

#include "qe/ECS/Core/Comp_Base.h"
#include "qe/Sound/SoundManager.h"

enum class EntitySound { None = -1, Collision, COUNT };

struct SoundParameter {
	static const int Max_SoundFrames = 8;

	SoundParameter() {
		for (int i = 0; i < Max_SoundFrames; ++i) {
			m_frames[i] = -1;
		}
	}

	std::string m_name;
	std::array<int, Max_SoundFrames> m_frames;
};

class Comp_SoundEmitter : public qe::Comp_Base {
public:
	static const int Max_EntitySounds = 4;

	Comp_SoundEmitter() : qe::Comp_Base(Component::SoundEmitter), m_soundID(-1) {}

	qe::SoundID GetSoundId() const { return m_soundID; }
	void SetSoundId(const qe::SoundID& id) { m_soundID = id; }
	
	void SetSound(const EntitySound& soundType, const std::string& name) {
		if (soundType == EntitySound::None || soundType == EntitySound::COUNT) return;

		m_parameters[static_cast<int>(soundType)].m_name = name;
		m_parameters[static_cast<int>(soundType)].m_frames[0] = 1;
	}

	const std::string& GetSound(const EntitySound& sound) {
		static std::string empty = "";

		return static_cast<int>(sound) < Max_EntitySounds ? m_parameters[static_cast<int>(sound)].m_name : empty;
	}

private:
	qe::SoundID m_soundID;
	std::array<SoundParameter, Max_EntitySounds> m_parameters;
};