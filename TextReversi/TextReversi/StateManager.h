#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "GameContext.h"
#include "GameState.h"
#include "GameStates.h"

using StateContainer = std::vector<std::pair<GameStateType, GameState*>>;
using StateFactory = std::unordered_map<GameStateType, std::function<GameState*(void)>>;

class StateManager
{
	public:
		StateManager(GameContext* context);
		~StateManager();

		void Run();

		void ChangeState(const GameStateType& type);

		bool IsRunning() const;
		void SetIsRunning(bool isRunning);

		GameContext* GetContext();

	private:
		bool m_isRunning;

		// Member variables
		StateContainer m_states;
		StateFactory m_stateFactory;
		GameContext* m_context;

		template <class T>
		void RegisterState(const GameStateType& type)
		{
			m_stateFactory[type] = [this]() -> GameState*
			{
				return new T(this);
			};
		}

		void CreateState(const GameStateType& type);
};