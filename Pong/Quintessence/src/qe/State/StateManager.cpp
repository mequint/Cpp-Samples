#include "qe/State/StateManager.h"

#include "qe/Event/EventManager.h"

namespace qe {
	StateManager::StateManager(Context* context) : m_context(context) {
	}

	StateManager::~StateManager()
	{
		for (auto& iter : m_states)
		{
			iter.second->Destroy();
			delete iter.second;
		}
	}

	void StateManager::Update(const sf::Time & time)
	{
		if (m_states.empty()) return;

		if (m_states.back().second->IsTranscendent() && m_states.size() > 1)
		{
			auto iter = m_states.end();
			while (iter != m_states.begin())
			{
				if (iter != m_states.end())
				{
					if (iter->second->IsTranscendent())
					{
						break;
					}
				}
				--iter;
			}

			while (iter != m_states.end())
			{
				iter->second->Update(time);
				++iter;
			}
		}
		else
		{
			m_states.back().second->Update(time);
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
				if (iter != m_states.end())
				{
					if (!iter->second->IsTransparent())
					{
						break;
					}
				}
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
			RemoveState(*m_toRemove.begin());
			m_toRemove.erase(m_toRemove.begin());
		}
	}

	Context* StateManager::GetContext()
	{
		return m_context;
	}

	bool StateManager::HasState(const StateType & type)
	{
		for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
		{
			if (iter->first == type)
			{
				auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);

				if (removed == m_toRemove.end())
				{
					return true;
				}

				return false;
			}
		}

		return false;
	}

	void StateManager::ChangeState(const StateType & type)
	{
		m_context->m_eventManager->SetCurrentState(type);

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

	void StateManager::Remove(const StateType & type)
	{
		m_toRemove.push_back(type);
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
}