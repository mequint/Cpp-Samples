#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "Context.h"
#include "State.h"
#include "GameStates.h"

using States = std::vector<std::pair<StateType, State*>>;
using StateTypes = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<State*(void)>>;

class StateManager
{
	public:
		StateManager(Context* context);
		~StateManager();

		void Update(float dt);
		void Draw();
		void ProcessRequests();

		Context* GetContext();

		void ChangeState(StateType stateType);
		void Remove(StateType stateType);

	private:
		// Member variables
		States m_states;
		StateTypes m_toRemove;
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

		void createState(StateType stateType);
		void removeState(StateType stateType);
};