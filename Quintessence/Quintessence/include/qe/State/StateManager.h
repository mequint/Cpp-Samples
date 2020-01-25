#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "BaseState.h"
#include "StateObserver.h"
#include "StateType.h"

namespace qe {
	struct Context;

	using StateContainer = std::vector<std::pair<StateType, std::unique_ptr<BaseState>>>;
	using TypeContainer = std::vector<StateType>;
	using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

	using StateObservers = std::vector<StateObserver*>;

	class StateManager {
	public:
		StateManager(Context* context);
		~StateManager();

		void update(const sf::Time& time);
		void draw();
		void removeDeadStates();

		Context* getContext();

		template <class T>
		T* getCurrentState() {
			return dynamic_cast<T*>(&(*m_states.back().second.get()));
		}

		bool hasState(const StateType& type);

		void changeState(const StateType& type);
		void remove(const StateType& type);

		template <class T>
		void registerState(const StateType& type) {
			m_stateFactory[type] = [this]()->BaseState* {
				return new T(this);
			};
		}

		void registerObserver(StateObserver* observer);
		void removeObserver(StateObserver* observer);

	private:
		void _createState(const StateType& type);
		void _removeState(const StateType& type);

		Context* m_context;

		StateContainer m_states;
		TypeContainer m_toRemove;
		StateFactory m_stateFactory;

		StateObservers m_observers;
	};
}