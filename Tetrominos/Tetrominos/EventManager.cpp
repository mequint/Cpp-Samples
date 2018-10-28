#include "EventManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager(bool loadFromFile) : m_currentState(StateType(0)), m_hasFocus(true)
{
	if (loadFromFile)
	{
		LoadBindings();
	}
}

EventManager::~EventManager()
{
	for (auto& iter : m_bindings)
	{
		delete iter.second;
	}
}

/// Manually adds a binding to the event manager
bool EventManager::AddBinding(const std::string& name, int eventType, int code)
{
	Binding* binding = new Binding(name);
	EventType type = EventType(eventType);
	EventInfo eventInfo(code);

	binding->BindEvent(type, eventInfo);

	if (!AddBinding(binding))
	{
		delete binding;
		binding = nullptr;
		return false;
	}

	binding = nullptr;
	return true;
}

bool EventManager::AddBinding(Binding* binding)
{
	if (m_bindings.find(binding->m_name) != m_bindings.end()) return false;

	return m_bindings.emplace(binding->m_name, binding).second;
}

bool EventManager::RemoveBinding(std::string name)
{
	auto iter = m_bindings.find(name);
	if (iter == m_bindings.end()) return false;

	delete iter->second;
	m_bindings.erase(iter);

	return true;
}

void EventManager::SetCurrentState(StateType state)
{
	m_currentState = state;
}

void EventManager::SetFocus(bool focus)
{
	m_hasFocus = focus;
}

bool EventManager::RemoveCallback(StateType state, const std::string& name)
{
	if (m_callbacks.empty()) return false;

	auto iter = m_callbacks.find(state);
	if (iter == m_callbacks.end()) return false;

	auto iter2 = iter->second.find(name);
	if (iter2 == iter->second.end()) return false;

	iter->second.erase(name);
	return true;
}

void EventManager::HandleEvent(sf::Event & event)
{
	for (auto& bIter : m_bindings)
	{
		Binding* binding = bIter.second;

		for (auto& eIter : binding->m_events)
		{
			EventType sfmlEvent = (EventType)event.type;
			if (eIter.first != sfmlEvent) continue;

			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (eIter.second.m_code == event.key.code)
				{
					if (binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = eIter.second.m_code;
					}

					++(binding->m_count);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				if (eIter.second.m_code == event.mouseButton.button)
				{
					binding->m_details.m_mouse.x = event.mouseButton.x;
					binding->m_details.m_mouse.y = event.mouseButton.y;

					if (binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = eIter.second.m_code;
					}

					++(binding->m_count);
					break;
				}
			}
			else if (sfmlEvent == EventType::JButtonDown || sfmlEvent == EventType::JButtonUp)
			{
				// How will we know how the buttons are mapped?  
				// Some joysticks may have the buttons enumerated differently...
				if (eIter.second.m_code == event.joystickButton.button)
				{
					if (binding->m_details.m_keyCode != -1)
					{
						binding->m_details.m_keyCode = eIter.second.m_code;
					}

					++(binding->m_count);
					break;
				}
			}
			else
			{
				if (sfmlEvent == EventType::MouseWheel)
				{
					binding->m_details.m_mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized)
				{
					binding->m_details.m_size.x = event.size.width;
					binding->m_details.m_size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
				{
					binding->m_details.m_textEntered = event.text.unicode;
				}
				else if (sfmlEvent == EventType::JoystickMoved)
				{
					binding->m_details.m_joystickXY.x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
					binding->m_details.m_joystickXY.y = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);

					// Store the axis positions
					/*
					for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
					{
						std::vector<sf::Joystick::Axis> axisList; //= joystickAxisContainer.find(i);
						for (auto axis : axisList)
						{
							float pos = sf::Joystick::getAxisPosition(i, axis);
							// m_joystickMoves.emplace_back(i, axis, pos);
						}
					}
					*/
				}
				else if (sfmlEvent == EventType::MouseMoved)
				{
					binding->m_details.m_mouse.x = event.mouseMove.x;
					binding->m_details.m_mouse.y = event.mouseMove.y;
				}

				++(binding->m_count);
			}

		}
	}
}

void EventManager::Update()
{
	if (!m_hasFocus) return;

	for (auto& bIter : m_bindings)
	{
		Binding* binding = bIter.second;

		for (auto& eIter : binding->m_events)
		{
			switch (eIter.first)
			{
				case EventType::Keyboard:
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eIter.second.m_code)))
					{
						if (binding->m_details.m_keyCode != -1)
						{
							binding->m_details.m_keyCode = eIter.second.m_code;
						}

						++(binding->m_count);
					}

					break;
				}

				case EventType::Mouse:
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eIter.second.m_code)))
					{
						if (binding->m_details.m_keyCode != -1)
						{
							binding->m_details.m_keyCode = eIter.second.m_code;
						}

						++(binding->m_count);
					}

					break;
				}

				case EventType::Joystick:
				{
					// Right now we are only looking button presses on controller one...
					if (sf::Joystick::isButtonPressed(0, (unsigned int)eIter.second.m_code))
					{
						if (binding->m_details.m_keyCode != -1)
						{
							binding->m_details.m_keyCode = eIter.second.m_code;
						}

						++(binding->m_count);
					}

					break;
				}
			}
		}

		if (binding->m_events.size() == binding->m_count)
		{
			auto stateCallbacks = m_callbacks.find(m_currentState);
			auto globalCallbacks = m_callbacks.find(StateType(0));

			if (stateCallbacks != m_callbacks.end())
			{
				auto callIter = stateCallbacks->second.find(binding->m_name);
				if (callIter != stateCallbacks->second.end())
				{
					callIter->second(&binding->m_details);
				}
			}

			if (globalCallbacks != m_callbacks.end())
			{
				auto callIter = globalCallbacks->second.find(binding->m_name);
				if (callIter != globalCallbacks->second.end())
				{
					callIter->second(&binding->m_details);
				}
			}
		}

		binding->m_count = 0;
		binding->m_details.Clear();
	}
}

sf::Vector2i EventManager::GetMousePos(sf::RenderWindow * window)
{
	return (window) ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
}

// TODO: Is there another way to do this?  Load it manually? XML, JSON?
void EventManager::LoadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");	// System file path? Assets files?
	if (!bindings.is_open())
	{
		std::cout << "ERROR: Failed to load keys.cfg" << std::endl;		// TODO: Move to log file...
		return;
	}

	std::string line;
	while (std::getline(bindings, line))
	{
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;

		Binding* binding = new Binding(callbackName);

		while (!keystream.eof())
		{
			std::string keyVal;
			keystream >> keyVal;

			int start = 0;
			int end = keyVal.find(delimiter);
			if (end == std::string::npos)
			{
				delete binding;
				binding = nullptr;
				break;
			}

			EventType type = EventType(std::stoi(keyVal.substr(start, end - start)));
			int code = std::stoi(keyVal.substr(end + delimiter.length(), keyVal.find(delimiter, end + delimiter.length())));

			EventInfo eventInfo;
			eventInfo.m_code = code;

			binding->BindEvent(type, eventInfo);
		}

		if (!AddBinding(binding)) delete binding;
		binding = nullptr;
	}

	bindings.close();
}