#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "Context.h"
#include "State.h"
#include "GameStates.h"

using StateContainer = std::vector<std::pair<StateType, State*>>;
using StateFactory = std::unordered_map<StateType, std::function<State*(void)>>;

class StateManager
{
	public:
		StateManager(Context* context);
		~StateManager();

		void ProcessInput();
		void Update();
		void Draw();

		void ChangeState(const StateType& type);

		bool IsRunning() const;
		void SetIsRunning(bool isRunning);

		Context* GetContext();

	private:
		bool m_isRunning;

		// Member variables
		StateContainer m_states;
		StateFactory m_stateFactory;
		Context* m_context;

		template <class T>
		void RegisterState(const StateType& type)
		{
			m_stateFactory[type] = [this]() -> State*
			{
				return new T(this);
			};
		}

		void CreateState(const StateType& type);
};