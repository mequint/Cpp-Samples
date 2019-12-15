#pragma once

namespace qe {
	class EntityManager;
	class FontManager;
	class EventManager;
	class StateManager;
	class SystemManager;
	class TextureManager;
	class Window;

	struct Context {
		Context() :
			m_entityManager(nullptr),
			m_eventManager(nullptr),
			m_fontManager(nullptr),
			m_stateManager(nullptr),
			m_systemManager(nullptr),
			m_textureManager(nullptr),
			m_window(nullptr) {
		}

		EntityManager* m_entityManager;
		EventManager* m_eventManager;
		FontManager* m_fontManager;
		StateManager* m_stateManager;
		SystemManager* m_systemManager;
		TextureManager* m_textureManager;
		Window* m_window;
	};
}