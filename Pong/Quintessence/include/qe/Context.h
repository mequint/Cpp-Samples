#pragma once

namespace qe{
	class AudioManager;
	class EntityManager;
	class EventManager;
	class FontManager;
	class TextureManager;
	class RandomGenerator;
	class SoundManager;
	class SystemManager;
	class Window;

	struct Context
	{
		Context() : 
			m_audioManager(nullptr),
			m_entityManager(nullptr), 
			m_eventManager(nullptr), 
			m_fontManager(nullptr), 
			m_randomGenerator(nullptr),
			m_systemManager(nullptr), 
			m_window(nullptr) {
		}

		AudioManager* m_audioManager;
		EntityManager* m_entityManager;
		EventManager* m_eventManager;
		FontManager* m_fontManager;
		TextureManager* m_textureManager;
		RandomGenerator* m_randomGenerator;
		SoundManager* m_soundManager;
		SystemManager* m_systemManager;
		Window* m_window;
	};
}