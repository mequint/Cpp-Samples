#include "qe/Window/EventManager.h"

#include "qe/State/StateTypes.h"

qe::EventManager::EventManager() :
	m_hasFocus(true) {}

qe::EventManager::~EventManager() {}

bool qe::EventManager::addBinding(const std::string & name, int eventType, int code) {
	if (m_bindings.find(name) != m_bindings.end()) return false;

	auto binding = std::make_shared<EventBinding>(name);
	EventType type = static_cast<EventType>(eventType);
	EventInfo eventInfo(code);

	binding->bindEvent(type, eventInfo);

	return m_bindings.emplace(binding->m_name, std::move(binding)).second;
}

bool qe::EventManager::addBinding(std::shared_ptr<EventBinding> binding) {
	if (m_bindings.find(binding->m_name) != m_bindings.end()) return false;

	return m_bindings.emplace(binding->m_name, std::move(binding)).second;
}

bool qe::EventManager::removeBinding(const std::string & name) {
	auto iter = m_bindings.find(name);
	if (iter == m_bindings.end()) return false;

	m_bindings.erase(iter);
	return true;
}

void qe::EventManager::setFocus(bool focus) {
	m_hasFocus = true;
}

bool qe::EventManager::removeCallback(const StateType & state, const std::string & name) {
	auto iter = m_callbacks.find(state);
	if (iter == m_callbacks.end()) return false;

	auto iter2 = iter->second.find(name);
	if (iter2 == iter->second.end()) return false;

	iter->second.erase(name);
	return true;
}

void qe::EventManager::handleEvent(sf::Event& event) {
	for (auto& bIter : m_bindings) {
		auto& binding = bIter.second;

		for (auto& eIter : binding->m_events) {
			EventType sfmlEvent = static_cast<EventType>(event.type);
			
			if (eIter.first != sfmlEvent) continue;

			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (eIter.second.m_eventCode == event.key.code) {
					if (binding->m_details.m_keyCode == -1) {
						binding->m_details.m_keyCode = eIter.second.m_eventCode;
					}

					if (sfmlEvent == EventType::KeyDown) {
						binding->m_details.m_controlPressed = event.key.control;
						binding->m_details.m_altPressed = event.key.alt;
						binding->m_details.m_shiftPressed = event.key.shift;
						binding->m_details.m_systemPressed = event.key.system;
					}

					++(binding->count);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (eIter.second.m_eventCode == event.mouseButton.button) {
					binding->m_details.m_mouse.x = event.mouseButton.x;
					binding->m_details.m_mouse.y = event.mouseButton.y;

					if (binding->m_details.m_keyCode == -1) {
						binding->m_details.m_keyCode = eIter.second.m_eventCode;
					}

					++(binding->count);
					break;
				}
			}
			else {
				if (sfmlEvent == EventType::MouseWheel) {
					binding->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					binding->m_details.m_size.x = event.size.width;
					binding->m_details.m_size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					binding->m_details.m_textEntered = event.text.unicode;
				}

				++(binding->count);
			}
		}
	}
}

void qe::EventManager::update() {
	if (!m_hasFocus) return;

	for (auto& bIter : m_bindings) {
		auto& binding = bIter.second;

		for (auto& eIter : binding->m_events) {
			switch (eIter.first) {
				case EventType::Keyboard: {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eIter.second.m_eventCode))) {
						if (binding->m_details.m_keyCode != -1) {
							binding->m_details.m_keyCode = eIter.second.m_eventCode;
						}

						++(binding->count);
					}
					break;
				}

				case EventType::Mouse: {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eIter.second.m_eventCode))) {
						if (binding->m_details.m_keyCode != -1) {
							binding->m_details.m_keyCode = eIter.second.m_eventCode;
						}

						++(binding->count);
					}
				}

				case EventType::Joystick: {
					// TODO: Expand
					break;
				}
			}

			if (binding->m_events.size() == binding->count) {
				// Handle global events
				auto globalCallbacks = m_callbacks.find(StateType(0));
				if (globalCallbacks != m_callbacks.end()) {
					auto callIter = globalCallbacks->second.find(binding->m_name);
					if (callIter != globalCallbacks->second.end()) {
						callIter->second(&binding->m_details);
					}
				}

				if (m_currentState == StateType(0)) continue;

				// Handle state based events
				auto stateCallbacks = m_callbacks.find(m_currentState);
				if (stateCallbacks != m_callbacks.end()) {
					auto callIter = stateCallbacks->second.find(binding->m_name);

					if (callIter != stateCallbacks->second.end()) {
						callIter->second(&binding->m_details);
					}
				}
			}
		}

		binding->count = 0;
		binding->m_details.clear();
	}
}

sf::Vector2i qe::EventManager::getMousePosition(sf::Window * window) const {
	return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
}

void qe::EventManager::changeState(const StateType & state) {
	_setState(state);
}

void qe::EventManager::removeState(const StateType & state) {
	m_callbacks.erase(state);
}