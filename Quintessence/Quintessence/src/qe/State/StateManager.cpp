#include "qe/State/StateManager.h"

#include "qe/Context.h"
#include "qe/Window/Window.h"

qe::StateManager::StateManager(Context * context) :
	m_context(context) {
}

qe::StateManager::~StateManager() {
	for (auto& iter : m_states) {
		iter.second->onDestroy();
	}
}

void qe::StateManager::update(const sf::Time & time) {
	if (m_states.empty()) { return; }

	if (m_states.back().second->isTranscendent() && m_states.size() > 1) {
		auto iter = m_states.end();
		while (iter != m_states.begin()) {
			if (iter != m_states.end()) {
				if (!iter->second->isTranscendent()) {
					break;
				}
			}

			--iter;
		}

		for (; iter != m_states.end(); ++iter) {
			iter->second->update(time);
		}
	}
	else { 
		m_states.back().second->update(time);
	}
}

void qe::StateManager::draw() {
	if (m_states.empty()) { return; }

	if (m_states.back().second->isTransparent() && m_states.size() > 1) {
		auto iter = m_states.end();
		while (iter != m_states.begin()) {
			if (iter != m_states.end()) {
				if (!iter->second->isTranscendent()) {
					break;
				}
			}

			--iter;
		}

		for (; iter != m_states.end(); ++iter) {
			m_context->m_window->getRenderWindow()->setView(iter->second->getView());
			iter->second->draw();
		}
	}
	else {
		m_states.back().second->draw();
	}
}

void qe::StateManager::removeDeadStates() {
	while (m_toRemove.begin() != m_toRemove.end()) {
		_removeState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

qe::Context * qe::StateManager::getContext() { return m_context; }

bool qe::StateManager::hasState(const StateType & type) {
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first == type) {
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if (removed == m_toRemove.end()) return true;

			return false;
		}
	}

	return false;
}

void qe::StateManager::changeState(const StateType & type) {
	if (!m_states.empty() && m_states.back().first == type) return;

	// Tell the observers that a state change is occuring
	for (auto& observer : m_observers) {
		observer->changeState(type);
	}

	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first != type) continue;

		m_states.back().second->onExit();

		StateType tempType = iter->first;
		std::unique_ptr<BaseState> tempState = std::move(iter->second);

		m_states.erase(iter);
		tempState->onEnter();

		auto& view = tempState->getView();
		m_states.emplace_back(tempType, std::move(tempState));

		m_context->m_window->getRenderWindow()->setView(view);

		return;
	}

	if (!m_states.empty()) {
		m_states.back().second->onExit();
	}
	
	_createState(type);
	m_states.back().second->onEnter();
	m_context->m_window->getRenderWindow()->setView(m_states.back().second->getView());
}

void qe::StateManager::remove(const StateType & type) {
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first != type) continue;

		iter->second->onDestroy();
		m_toRemove.push_back(type);

		for (auto& observer : m_observers) {
			observer->removeState(type);
		}
	}
}

void qe::StateManager::registerObserver(StateObserver * observer) {
	m_observers.emplace_back(observer);
}

void qe::StateManager::removeObserver(StateObserver * observer) {
	m_observers.erase(std::find_if(m_observers.begin(), m_observers.end(),
		[observer](StateObserver* iter) { return iter == observer; }
	));
}

void qe::StateManager::_createState(const StateType & type) {
	auto stateFactory = m_stateFactory.find(type);
	if (stateFactory == m_stateFactory.end()) return;

	std::unique_ptr<BaseState> state(stateFactory->second());
	state->m_view = m_context->m_window->getRenderWindow()->getDefaultView();

	m_states.emplace_back(type, std::move(state));
	m_states.back().second->onCreate();
}

void qe::StateManager::_removeState(const StateType & type) {
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter) {
		if (iter->first != type) continue;

		m_states.erase(iter);
		return;
	}
}