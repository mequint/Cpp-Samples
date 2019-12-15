#pragma once

#include "StateType.h"

namespace qe {
	class StateManager;

	class StateObserver {
	public:
		StateObserver() : m_currentState(static_cast<StateType>(0)) {}
		virtual ~StateObserver() {}

		virtual void createState(const StateType& state) {}
		virtual void changeState(const StateType& state) = 0;
		virtual void removeState(const StateType& state) = 0;

		StateType getCurrentState() const { return m_currentState; }

	protected:
		void _setState(const StateType& state) { m_currentState = state; }

		StateType m_currentState;
	};
}