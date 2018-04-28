#include "StateManager.h"

#include "GameStates.h"

StateManager::StateManager(Context* context) :
	m_context(context),
	m_isRunning(true)
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

void StateManager::ProcessInput()
{
}

void StateManager::Update()
{
	if (m_states.empty()) return;

	m_states.back().second->Update();
}

void StateManager::Draw()
{
	if (m_states.empty()) return;
	
	m_states.back().second->Draw();
}

void StateManager::ChangeState(const StateType& type)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->first == type)
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

	CreateState(type);
	m_states.back().second->Activate();
}

bool StateManager::IsRunning() const { return m_isRunning; }
void StateManager::SetIsRunning(bool isRunning) { m_isRunning = isRunning; }


Context* StateManager::GetContext()
{
	return m_context;
}

void StateManager::CreateState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) return;

	State* state = newState->second();
	m_states.emplace_back(type, state);
	state->Initialize();
}