#include "StateManager.h"

#include "GameStates.h"

StateManager::StateManager(Context* context) :
	m_context(context)
{
	RegisterState<IntroState>(StateType::Intro);
}

StateManager::~StateManager()
{
	for (auto& iter : m_states)
	{
		iter.second->Cleanup();
		delete iter.second;
	}
}

void StateManager::Update(float dt)
{
	if (m_states.empty()) return;

	if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
	{
		auto iter = m_states.end();

		while (iter != m_states.begin())
		{
			if (iter != m_states.end() && !iter->second->IsTranscendent()) break;
		
			--iter;
		}
		
		while (iter != m_states.end())
		{
			// Need to add the concept of time...
			iter->second->Update(dt);

			++iter;
		}
	}
	else
	{
		m_states.back().second->Update(dt);
	}
}

void StateManager::Draw()
{
	if (m_states.empty()) return;
	
	if (m_states.back().second->IsTransparent() && m_states.size() > 1)
	{
		auto iter = m_states.end();

		while (iter != m_states.begin())
		{
			if (iter != m_states.end() && !iter->second->IsTransparent()) break;

			--iter;
		}

		while (iter != m_states.end())
		{
			iter->second->Draw();
			++iter;
		}
	}
	else
	{
		m_states.back().second->Draw();
	}
}

void StateManager::ProcessRequests()
{
	while (m_toRemove.begin() != m_toRemove.end())
	{
		removeState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

void StateManager::ChangeState(StateType stateType)
{
	m_context->EventManager->SetCurrentState(stateType);

	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == stateType)
		{
			m_states.back().second->Deactivate();

			StateType tempType = iter->first;
			State* tempState = iter->second;

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

	createState(stateType);
	m_states.back().second->Activate();
}

void StateManager::Remove(StateType stateType)
{
	m_toRemove.push_back(stateType);
}

Context* StateManager::GetContext()
{
	return m_context;
}

void StateManager::createState(StateType stateType)
{
	auto newState = m_stateFactory.find(stateType);
	if (newState == m_stateFactory.end()) return;

	State* state = newState->second();
	m_states.emplace_back(stateType, state);
	state->Initialize();
}

void StateManager::removeState(StateType stateType)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == stateType)
		{
			iter->second->Cleanup();
			delete iter->second;
			m_states.erase(iter);
			return;
		}
	}
}