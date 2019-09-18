#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "qe\State\BaseState.h"
#include "qe\Context.h"

namespace qe {
	// TODO: Is there anyway to move this out to the game layer???
	enum class StateType { Title = 1, PreGame, Game, GameOver, Paused, Credits };

	using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
	using TypeContainer = std::vector<StateType>;
	using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

	class StateManager
	{
		public:
			StateManager(Context* context);
			~StateManager();

			void Update(const sf::Time& time);
			void Draw();
			void ProcessRequests();

			Context* GetContext();
			bool HasState(const StateType& type);

			void ChangeState(const StateType& type);
			void Remove(const StateType& type);

			template <class T>
			void RegisterState(const StateType& type)
			{
				m_stateFactory[type] = [this]()->BaseState*
				{
					return new T(this);
				};
			}

		private:
			void CreateState(const StateType& type);
			void RemoveState(const StateType& type);

			Context* m_context;

			StateContainer m_states;
			TypeContainer m_toRemove;
			StateFactory m_stateFactory;
	};
}