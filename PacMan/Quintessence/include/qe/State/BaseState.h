#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

namespace qe {
	class StateManager;

	class BaseState {
		friend class StateManager;

	public:
		BaseState(StateManager* stateManager) : m_stateManager(stateManager) {}
		virtual ~BaseState() {}

		virtual void onCreate() = 0;
		virtual void onDestroy() = 0;

		virtual void onEnter() = 0;
		virtual void onExit() = 0;

		virtual void update(const sf::Time& time) = 0;
		virtual void draw() = 0;

		void setTransparent(bool transparent) { m_transparent = transparent; }
		bool isTransparent() const { return m_transparent; }
		void setTranscendent(bool transcendent) { m_transcendent = transcendent; }
		bool isTranscendent() const { return m_transcendent; }

		sf::View& getView() { return m_view; }
		StateManager* getStateManager() { return m_stateManager; }

	protected:
		StateManager* m_stateManager;

		bool m_transparent;
		bool m_transcendent;

		sf::View m_view;
	};
}

// TODO: Add Transitions to the base state? 