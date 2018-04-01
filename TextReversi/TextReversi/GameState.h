#pragma once

class StateManager;

class GameState
{
	friend class StateManager;

	public:
		GameState(StateManager* stateManager) :
			m_stateManager(stateManager)
		{}

		virtual ~GameState() {}

		virtual void Run() = 0;

		StateManager* GetStateManager() { return m_stateManager; }
	
	protected:
		StateManager * m_stateManager;
};