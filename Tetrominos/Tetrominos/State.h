#pragma once

class StateManager;

class State
{
	friend class StateManager;

	public:
		State(StateManager* stateManager) :
			m_stateManager(stateManager)
		{}

		virtual ~State() {}

		virtual void Run() = 0;

		StateManager* GetStateManager() { return m_stateManager; }

	protected:
		StateManager * m_stateManager;
};