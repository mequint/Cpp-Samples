#include "StateManager.h"

StateManager::StateManager() : 
	m_isRunning(true)
{
	RegisterState<IntroGameState>(GameStateType::Intro);
	RegisterState<MainMenuGameState>(GameStateType::MainMenu);
	RegisterState<DisplayRulesGameState>(GameStateType::DisplayRules);
	RegisterState<ExitingGameState>(GameStateType::Exiting);
}

StateManager::~StateManager()
{
	for (auto& iter : m_states)
	{
		delete iter.second;
	}
}

void StateManager::GetInput()
{
	if (m_states.empty()) return;
	m_states.back().second->GetInput();
}

void StateManager::Update()
{
	if (m_states.empty()) return;
	m_states.back().second->Update();
}

void StateManager::Display()
{
	if (m_states.empty()) return;
	m_states.back().second->Display();
}

void StateManager::ChangeState(const GameStateType& type)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == type)
		{
			GameStateType tempType = iter->first;
			GameState* tempState = iter->second;

			m_states.erase(iter);
			m_states.emplace_back(tempType, tempState);

			return;
		}
	}

	CreateState(type);
}

void StateManager::CreateState(const GameStateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) return;

	GameState* state = newState->second();
	m_states.emplace_back(type, state);
}