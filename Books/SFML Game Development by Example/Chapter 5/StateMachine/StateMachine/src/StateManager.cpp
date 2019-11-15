#include "StateManager.h"

StateManager::StateManager(SharedContext* shared) :
	m_context(shared) {

	RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager() {
	for (auto& iter : m_states) {
		iter.second->OnDestroy();
		delete iter.second;
	}
}

void StateManager::Update(const sf::Time & time) {
	if (m_states.empty()) return;

	if (m_states.back().second->IsTranscendent() && m_states.size() > 1) {
		auto iter = m_states.end();
		while (iter != m_states.begin()) {
			if (iter != m_states.end()) {
				if (!iter->second->IsTranscendent()) {
					break;
				}
			}

			--iter;
		}

		for (; iter != m_states.end(); ++iter) {
			iter->second->Update(time);
		}
	}
	else {
		m_states.back().second->Update(time);
	}
}

void StateManager::Draw() {
	if (m_states.empty()) return;

	if (m_states.back().second->IsTransparent() && m_states.size() > 1) {
		auto iter = m_states.end();
		while (iter != m_states.begin()) {
			if (iter != m_states.end()) {
				if (!iter->second->IsTransparent()) {
					break;
				}
			}

			--iter;
		}

		for (; iter != m_states.end(); ++iter) {
			iter->second->Draw();
		}
	}
	else {
		m_states.back().second->Draw();
	}
}

void StateManager::ProcessRequests() {
	while (m_toRemove.begin() != m_toRemove.end()) {
		RemoveState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

SharedContext * StateManager::GetContext() {
	return m_context;
}

bool StateManager::HasState(const StateType & type) {
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first == type) {
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if (removed == m_toRemove.end()) return true;

			return false;
		}
	}

	return false;
}

void StateManager::SwitchTo(const StateType & type) {
	m_context->m_eventManager->SetCurrentState(type);

	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first == type) {
			m_states.back().second->Deactivate();

			StateType tempType = iter->first;
			BaseState* tempState = iter->second;
			m_states.erase(iter);
			m_states.emplace_back(tempType, tempState);
			tempState->Activate();

			return;
		}
	}

	if (!m_states.empty()) {
		m_states.back().second->Deactivate();
	}

	CreateState(type);
	m_states.back().second->Activate();
}

void StateManager::Remove(const StateType & type) {
	m_toRemove.push_back(type);
}

void StateManager::CreateState(const StateType & type) {
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) return;

	BaseState* state = newState->second();
	m_states.emplace_back(type, state);

	state->OnCreate();
}

void StateManager::RemoveState(const StateType & type) {
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first == type) {
			iter->second->OnDestroy();
			delete iter->second;

			m_states.erase(iter);
			return;
		}
	}
}