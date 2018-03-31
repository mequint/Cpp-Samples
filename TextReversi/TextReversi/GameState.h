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

		virtual void GetInput() = 0;
		virtual void Update() = 0;
		virtual void Display() = 0;

		StateManager* GetStateManager() { return m_stateManager; }
	
	protected:
		StateManager * m_stateManager;
};