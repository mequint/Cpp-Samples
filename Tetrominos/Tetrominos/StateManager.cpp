#include "StateManager.h"

StateManager::StateManager(GameContext* context) :
	m_context(context),
	m_isRunning(true)
{
}

StateManager::~StateManager()
{
	for (auto& iter : m_states)
	{
		delete iter.second;
	}
}

void StateManager::ProcessInput()
{
}

void StateManager::Update()
{
	if (m_states.empty()) return;
	m_states.back().second->Run();
}

void StateManager::Draw()
{
}

void StateManager::ChangeState(const StateType& type)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == type)
		{
			StateType tempType = iter->first;
			State* tempState = iter->second;

			m_states.erase(iter);
			m_states.emplace_back(tempType, tempState);

			return;
		}
	}

	CreateState(type);
}

void StateManager::CreateState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) return;

	State* state = newState->second();
	m_states.emplace_back(type, state);
}

bool StateManager::IsRunning() const { return m_isRunning; }
void StateManager::SetIsRunning(bool isRunning) { m_isRunning = isRunning; }


GameContext* StateManager::GetContext()
{
	return m_context;
}