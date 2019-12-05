#pragma once

namespace qe {
	class EventManager;
	class StateManager;
	class TextureManager;
	class Window;

	struct Context {
		Context() :
			m_eventManager(nullptr),
			m_stateManager(nullptr),
			m_textureManager(nullptr),
			m_window(nullptr) {
		}

		EventManager* m_eventManager;
		StateManager* m_stateManager;
		TextureManager* m_textureManager;
		Window* m_window;
	};
}