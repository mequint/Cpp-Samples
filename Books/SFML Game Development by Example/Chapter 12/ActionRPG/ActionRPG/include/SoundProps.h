#pragma once

#include <string>

struct SoundProps {
	SoundProps(const std::string& name) :
		m_audioName(name),
		m_volume(100.0f),
		m_pitch(1.0f),
		m_minDistance(10.0f),
		m_attenuation(10.0f) {
	}

	std::string m_audioName;
	float m_volume;
	float m_pitch;
	float m_minDistance;
	float m_attenuation;
};