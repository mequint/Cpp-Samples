#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "BaseState.h"
#include "Context.h"

enum class StateType { Game };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
	public:
		StateManager(Context* context);
		~StateManager();

		void HandleEvents();
		void Update(const sf::Time& time);
		void Draw();

		Context* GetContext();

		//bool HasState(const StateType& type);

		void ChangeState(const StateType& type);
		//void Remove(const StateType& type);

	private:
		template <class T>
		void RegisterState(const StateType& type)
		{
			m_stateFactory[type] = [this]()->BaseState*
			{
				return new T(this);
			};
		}

		void CreateState(const StateType& type);
		void RemoveState(const StateType& type);

		Context* m_context;

		StateContainer m_states;
		StateFactory m_stateFactory;
};