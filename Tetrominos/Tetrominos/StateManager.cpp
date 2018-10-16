#include "StateManager.h"

#include "State_Game.h"

StateManager::StateManager(Context* context) : m_context(context)
{
	RegisterState<State_Game>(StateType::Game);
}

StateManager::~StateManager()
{
	for (auto& iter : m_states)
	{
		iter.second->Destroy();
		delete iter.second;
	}
}

void StateManager::HandleEvents()
{
	m_states.back().second->HandleEvents();
}

void StateManager::Update(const sf::Time & time)
{
	if (m_states.empty()) return;

	m_states.back().second->Update(time);
}

void StateManager::Draw()
{
	if (m_states.empty()) return;

	m_states.back().second->Draw();
}

Context* StateManager::GetContext()
{
	return m_context;
}

void StateManager::ChangeState(const StateType & type)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == type)
		{
			m_states.back().second->Deactivate();

			StateType tempType = iter->first;
			BaseState* tempState = iter->second;

			m_states.erase(iter);
			m_states.emplace_back(tempType, tempState);

			tempState->Activate();
			return;
		}
	}

	if (!m_states.empty())
	{
		m_states.back().second->Deactivate();
	}

	CreateState(type);
	m_states.back().second->Activate();
}

void StateManager::CreateState(const StateType & type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) return;

	BaseState* state = newState->second();
	m_states.emplace_back(type, state);
	state->Create();
}

void StateManager::RemoveState(const StateType & type)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == type)
		{
			iter->second->Destroy();
			delete iter->second;
			m_states.erase(iter);
			return;
		}
	}
}

/*
bool StateManager::HasState(const StateType & type)
{
	return false;
}
*/