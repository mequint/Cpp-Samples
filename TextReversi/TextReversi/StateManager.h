#pragma once

#include <functional>
#include <vector>
#include <unordered_map>

#include "GameState.h"
#include "GameStates.h"

using StateContainer = std::vector<std::pair<GameStateType, GameState*>>;
using StateFactory = std::unordered_map<GameStateType, std::function<GameState*(void)>>;

class StateManager
{
	public:
		StateManager();
		~StateManager();

		void GetInput();
		void Update();
		void Display();

		void ChangeState(const GameStateType& type);

		// Temporary - move this into a game context
		bool IsRunning() const { return m_isRunning; }
		void SetIsRunning(bool isRunning) { m_isRunning = isRunning; }

	private:
		// Temp variable
		bool m_isRunning;

		// Member variables
		StateContainer m_states;
		StateFactory m_stateFactory;

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