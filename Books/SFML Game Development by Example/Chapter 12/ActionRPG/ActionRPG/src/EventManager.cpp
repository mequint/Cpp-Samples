#include "EventManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Utilities.h"

EventManager::EventManager() : 
	m_currentState(StateType(0)), 
	m_hasFocus(true) {
	LoadBindings();
}

EventManager::~EventManager() {
	for (auto& iter : m_bindings) {
		delete iter.second;
	}
}

bool EventManager::AddBinding(Binding * binding) {
	if (m_bindings.find(binding->m_name) != m_bindings.end()) return false;

	return m_bindings.emplace(binding->m_name, binding).second;
}

bool EventManager::RemoveBinding(const std::string & name) {
	auto iter = m_bindings.find(name);
	if (iter == m_bindings.end()) return false;

	delete iter->second;
	m_bindings.erase(iter);

	return true;
}

void EventManager::SetCurrentState(const StateType & state)  {
	m_currentState = state;
}

void EventManager::SetFocus(bool focus) {
	m_hasFocus = focus;
}

void EventManager::HandleEvent(sf::Event & event) {
	for (auto& bIter : m_bindings) {
		Binding* bind = bIter.second;

		for (auto& eIter : bind->m_events) {
			EventType sfmlEvent = static_cast<EventType>(event.type);

			if (eIter.first == EventType::GUI_Click || eIter.first == EventType::GUI_Release ||
				eIter.first == EventType::GUI_Hover || eIter.first == EventType::GUI_Leave) {
				continue;
			}

			if (eIter.first != sfmlEvent) continue;

			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (eIter.second.m_code == event.key.code) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = eIter.second.m_code;
					}

					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonDown) {
				if (eIter.second.m_code == event.mouseButton.button) {
					bind->m_details.m_mouse.x = event.mouseButton.x;
					bind->m_details.m_mouse.y = event.mouseButton.y;

					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = eIter.second.m_code;
					}

					++(bind->c);
					break;
				}
			}
			else {
				if (sfmlEvent == EventType::MouseWheel) {
					bind->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->m_details.m_size.x = event.size.width;
					bind->m_details.m_size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->m_details.m_textEntered = event.text.unicode;
				}

				++(bind->c);
			}
		}
	}
}

void EventManager::HandleEvent(GUI_Event & event) {
	for (auto& bIter : m_bindings) {
		Binding* bind = bIter.second;

		for (auto& eIter : bind->m_events) {
			if (eIter.first != EventType::GUI_Click && eIter.first != EventType::GUI_Release &&
				eIter.first != EventType::GUI_Hover && eIter.first != EventType::GUI_Leave) {
				continue;
			}

			if ((eIter.first == EventType::GUI_Click && event.m_type != GUI_EventType::Click) ||
				(eIter.first == EventType::GUI_Release && event.m_type != GUI_EventType::Release) ||
				(eIter.first == EventType::GUI_Hover && event.m_type != GUI_EventType::Hover) ||
				(eIter.first == EventType::GUI_Leave && event.m_type != GUI_EventType::Leave)) {
				continue;
			}

			if (strcmp(eIter.second.m_gui.m_interface, event.m_interface) ||
				strcmp(eIter.second.m_gui.m_element, event.m_element)) {
				continue;
			}

			bind->m_details.m_guiInterface = event.m_interface;
			bind->m_details.m_guiElement = event.m_element;
			++(bind->c);
		}
	}
}

void EventManager::Update() {
	if (!m_hasFocus) return;

	for (auto& bIter : m_bindings) {
		Binding* bind = bIter.second;

		for (auto& eIter : bind->m_events) {
			switch (eIter.first) {
				case EventType::Keyboard: {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eIter.second.m_code))) {
						if (bind->m_details.m_keyCode != -1) {
							bind->m_details.m_keyCode = eIter.second.m_code;
						}

						++(bind->c);
					}

					break;
				}

				case EventType::Mouse: {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eIter.second.m_code))) {
						if (bind->m_details.m_keyCode != -1) {
							bind->m_details.m_keyCode = eIter.second.m_code;
						}

						++(bind->c);
					}

					break;
				}

				case EventType::Joystick: {
					// TODO: Expand...
					break;
				}
			}
		}

		if (bind->m_events.size() == bind->c) {
			auto stateCallbacks = m_callbacks.find(m_currentState);
			auto otherCallbacks = m_callbacks.find(StateType(0));

			if (stateCallbacks != m_callbacks.end()) {
				auto callIter = stateCallbacks->second.find(bind->m_name);
				if (callIter != stateCallbacks->second.end()) {
					callIter->second(&bind->m_details);
				}
			}

			if (otherCallbacks != m_callbacks.end()) {
				auto callIter = otherCallbacks->second.find(bind->m_name);
				if (callIter != otherCallbacks->second.end()) {
					callIter->second(&bind->m_details);
				}
			}
		}

		bind->c = 0;
		bind->m_details.Clear();
	}
}

sf::Vector2i EventManager::GetMousePos(sf::RenderWindow * window) {
	return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
}

void EventManager::LoadBindings() {
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open(Utils::GetWorkingDirectory() + "keys.cfg");
	if (!bindings.is_open()) {
		std::cout << "! Failed to load keys.cfg" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;

		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;

			int start = 0;
			int end = keyval.find(delimiter);

			if (end == std::string::npos) {
				delete bind;
				bind = nullptr;
				break;
			}

			EventType type = static_cast<EventType>(std::stoi(keyval.substr(start, end - start)));
			EventInfo eventInfo;

			if (type == EventType::GUI_Click || type == EventType::GUI_Release ||
				type == EventType::GUI_Hover || type == EventType::GUI_Leave) {
				start = end + delimiter.length();
				end = keyval.find(delimiter, start);

				std::string window = keyval.substr(start, end - start);
				std::string element;

				if (end != std::string::npos) {
					start = end + delimiter.length();
					end = keyval.length();
					element = keyval.substr(start, end);
				}

				char* w = new char[window.length() + 1];
				char* e = new char[element.length() + 1];

				strcpy_s(w, window.length() + 1, window.c_str());
				strcpy_s(e, element.length() + 1, element.c_str());

				eventInfo.m_gui.m_interface = w;
				eventInfo.m_gui.m_element = e;
			}
			else {
				int code = stoi(keyval.substr(end + delimiter.length(),
					keyval.find(delimiter, end + delimiter.length())));

				eventInfo.m_code = code;
			}

			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind)) delete bind;

		bind = nullptr;
	}

	bindings.close();
}