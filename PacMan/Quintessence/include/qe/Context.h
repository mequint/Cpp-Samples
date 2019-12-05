#pragma once

namespace qe {
	class EventManager;
	class StateManager;
	class Window;

	struct Context {
		Context() :
			m_stateManager(nullptr),
			m_eventManager(nullptr),
			m_window(nullptr) {
		}

		EventManager* m_eventManager;
		StateManager* m_stateManager;
		Window* m_window;
	};
}