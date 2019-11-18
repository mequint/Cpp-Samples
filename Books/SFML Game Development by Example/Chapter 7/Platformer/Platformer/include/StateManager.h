#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_GameOver.h"
#include "State_Paused.h"
#include "SharedContext.h"

enum class StateType { Intro = 1, MainMenu, Game, Paused, GameOver, Credits };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager {
public:
	StateManager(SharedContext* shared);
	~StateManager();

	void Update(const sf::Time& time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& type);

	void SwitchTo(const StateType& type);
	void Remove(const StateType& type);

private:
	void CreateState(const StateType& type);
	void RemoveState(const StateType& type);

	template<class T>
	void RegisterState(const StateType& type) {
		m_stateFactory[type] = [this]() -> BaseState* {
			return new T(this);
		};
	}

	SharedContext* m_context;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};