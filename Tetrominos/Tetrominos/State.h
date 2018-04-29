#pragma once

class StateManager;

class State
{
	friend class StateManager;

	public:
		State(StateManager* stateManager) :
			m_pStateManager(stateManager)
		{}

		virtual ~State() {}

		virtual void Initialize() = 0;
		virtual void Cleanup() = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;

		StateManager* GetStateManager();

		void SetTransparent(bool transparent);
		bool IsTransparent() const;
		void SetTranscendent(bool transcendent);
		bool IsTranscendent() const;

	protected:
		StateManager *m_pStateManager;
		bool m_transparent;
		bool m_transcendent;
};