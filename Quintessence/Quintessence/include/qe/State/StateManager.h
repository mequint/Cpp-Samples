#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "BaseState.h"
#include "StateObserver.h"

namespace qe {
	struct Context;

	using StateContainer = std::vector<std::pair<std::string, std::unique_ptr<BaseState>>>;
	using TypeContainer = std::vector<std::string>;
	using StateFactory = std::unordered_map<std::string, std::function<BaseState*(void)>>;

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

		bool hasState(const std::string& type);

		void changeState(const std::string& type);
		void remove(const std::string& type);

		template <class T>
		void registerState(const std::string& type) {
			m_stateFactory[type] = [this]()->BaseState* {
				return new T(this);
			};
		}

		void registerObserver(StateObserver* observer);
		void removeObserver(StateObserver* observer);

	private:
		void _createState(const std::string& type);
		void _removeState(const std::string& type);

		Context* m_context;

		StateContainer m_states;
		TypeContainer m_toRemove;
		StateFactory m_stateFactory;

		StateObservers m_observers;
	};
}