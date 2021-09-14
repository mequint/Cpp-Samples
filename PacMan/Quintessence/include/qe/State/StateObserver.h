#pragma once

namespace qe {
	class StateManager;

	class StateObserver {
	public:
		StateObserver() : m_currentState("Global") {}
		virtual ~StateObserver() {}

		virtual void createState(const std::string& state) {}
		virtual void changeState(const std::string& state) = 0;
		virtual void removeState(const std::string& state) = 0;

		std::string getCurrentState() const { return m_currentState; }

	protected:
		void _setState(const std::string& state) { m_currentState = state; }

		std::string m_currentState;
	};
}