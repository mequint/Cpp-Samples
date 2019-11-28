#pragma once

#include <array>

#include "C_Base.h"
#include "SoundManager.h"

enum class EntitySound { None = -1, Footstep, Attack, Hurt, Death };

struct SoundParameters {
	static const int Max_SoundFrames = 5;

	SoundParameters() {
		for (int i = 0; i < Max_SoundFrames; ++i) {
			m_frames[i] = -1;
		}
	}

	std::string m_sound;
	std::array<int, Max_SoundFrames> m_frames;
};

class C_SoundEmitter : public C_Base {
public:
	static const int Max_EntitySounds = 4;

	C_SoundEmitter() : C_Base(Component::SoundEmitter), m_soundID(-1) {}

	void ReadIn(std::stringstream& stream) {
		std::string mainDelimiter = ":";
		std::string frameDelimiter = ",";

		for (int i = 0; i < Max_EntitySounds; ++i) {
			std::string chunk;
			stream >> chunk;
			if (chunk == "") break;

			std::string sound = chunk.substr(0, chunk.find(mainDelimiter));
			std::string frames = chunk.substr(chunk.find(mainDelimiter) + mainDelimiter.length());

			m_params[i].m_sound = sound;

			size_t pos = 0;
			unsigned int frameNum = 0;

			while (frameNum < SoundParameters::Max_SoundFrames) {
				pos = frames.find(frameDelimiter);

				int frame = -1;

				if (pos != std::string::npos) {
					frame = stoi(frames.substr(0, pos));
					frames.erase(0, pos + frameDelimiter.length());
				}
				else {
					frame = stoi(frames);
					m_params[i].m_frames[frameNum] = frame;
					break;
				}

				m_params[i].m_frames[frameNum] = frame;
				++frameNum;
			}
		}
	}

	SoundID GetSoundID() { return m_soundID; }
	void SetSoundID(const SoundID& id) { m_soundID = id; }

	const std::string& GetSound(const EntitySound& snd) {
		static std::string empty = "";
		return (static_cast<int>(snd) < Max_EntitySounds) ? m_params[static_cast<int>(snd)].m_sound : empty;
	}

	bool IsSoundFrame(const EntitySound& snd, int frame) {
		if (static_cast<int>(snd) >= Max_EntitySounds) return false;

		for (int i = 0; i < SoundParameters::Max_SoundFrames; ++i) {
			if (m_params[static_cast<int>(snd)].m_frames[i] == -1) return false;
			if (m_params[static_cast<int>(snd)].m_frames[i] == frame) return true;
		}

		return false;
	}

	SoundParameters* GetParameters() { return &m_params[0]; }

private:
	SoundID m_soundID;
	std::array<SoundParameters, Max_EntitySounds> m_params;
};