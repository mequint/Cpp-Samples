#include "EventManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager() :
	m_currentState(StateType(0)),
	m_hasFocus(true)
{
	loadBindings();
}

EventManager::~EventManager()
{
	for (auto& iter : m_bindings)
	{
		delete iter.second;
	}
}

bool EventManager::AddBinding(Binding* binding)
{
	if (m_bindings.find(binding->Name) != m_bindings.end()) return false;

	return m_bindings.emplace(binding->Name, binding).second;
}

bool EventManager::RemoveBinding(std::string name)
{
	auto iter = m_bindings.find(name);
	if (iter == m_bindings.end()) return false;

	delete iter->second;
	m_bindings.erase(iter);
	return true;
}

void EventManager::SetCurrentState(StateType stateType)
{
	m_currentState = stateType;
}

void EventManager::SetFocus(bool focus)
{
	m_hasFocus = focus;
}

bool EventManager::RemoveCallback(StateType stateType, const std::string & name)
{
	auto iter = m_callbacks.find(stateType);
	if (iter == m_callbacks.end()) return false;

	auto iter2 = iter->second.find(name);
	if (iter2 == iter->second.end()) return false;
	
	iter->second.erase(name);
	return true;
}

void EventManager::HandleEvent(sf::Event & event)
{
	for (auto& bindingIter : m_bindings)
	{
		Binding* binding = bindingIter.second;

		for (auto& eventIter : binding->Events)
		{
			EventType eventType = (EventType)event.type;

			if (eventIter.first != eventType) continue;

			if (eventType == EventType::KeyDown || eventType == EventType::KeyUp)
			{
				if (eventIter.second.Code == event.key.code)
				{
					if (binding->Details.KeyCode != -1)
					{
						binding->Details.KeyCode = eventIter.second.Code;
					}

					++(binding->Count);
					break;
				}
			}
			else if (eventType == EventType::MouseButtonDown || eventType == EventType::MouseButtonUp)
			{
				if (eventIter.second.Code == event.mouseButton.button)
				{
					binding->Details.MouseX = event.mouseButton.x;
					binding->Details.MouseY = event.mouseButton.y;

					if (binding->Details.KeyCode != -1)
					{
						binding->Details.KeyCode = eventIter.second.Code;
					}

					++(binding->Count);
					break;
				}
			}
			else
			{
				if (eventType == EventType::MouseScroll)
				{
					binding->Details.MouseScrollDelta = event.mouseWheel.delta;
				}
				else if (eventType == EventType::WindowResized)
				{
					binding->Details.Width = event.size.width;
					binding->Details.Height = event.size.height;
				}
				else if (eventType == EventType::TextEntered)
				{
					binding->Details.TextEntered = event.text.unicode;
				}

				++(binding->Count);
			}
		}
	}
}

void EventManager::Update()
{
	if (!m_hasFocus) return;

	for (auto& bindingIter : m_bindings)
	{
		Binding* binding = bindingIter.second;

		for (auto& eventIter : binding->Events)
		{
			switch (eventIter.first)
			{
				case (EventType::Keyboard):
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eventIter.second.Code)))
					{
						if (binding->Details.KeyCode != -1)
						{
							binding->Details.KeyCode = eventIter.second.Code;
						}
						++(binding->Count);
					}
					break;
				}

				case (EventType::Mouse):
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eventIter.second.Code)))
					{
						if (binding->Details.KeyCode != -1)
						{
							binding->Details.KeyCode = eventIter.second.Code;
						}
						++(binding->Count);
					}
					break;
				}

				case (EventType::Joystick):
				{
					// Expand later
					break;
				}
			}
		}

		if (binding->Events.size() == binding->Count)
		{
			auto stateCallbacks = m_callbacks.find(m_currentState);
			auto otherCallbacks = m_callbacks.find(StateType(0));

			if (stateCallbacks != m_callbacks.end())
			{
				auto callbackIter = stateCallbacks->second.find(binding->Name);
				if (callbackIter != stateCallbacks->second.end())
				{
					callbackIter->second(&binding->Details);
				}
			}

			if (otherCallbacks != m_callbacks.end())
			{
				auto callbackIter = otherCallbacks->second.find(binding->Name);
				if (callbackIter != otherCallbacks->second.end())
				{
					callbackIter->second(&binding->Details);
				}
			}
		}

		binding->Count = 0;
		binding->Details.Clear();
	}
}

sf::Vector2i EventManager::GetMousePosition(sf::RenderWindow * window)
{
	return window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition();
}

void EventManager::loadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("Assets/bindings.txt");

	if (!bindings.is_open())
	{
		std::cout << "<EventManager::loadBindings>: Failed to load bindings.txt" << std::endl;
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
			std::string keyValue;
			keystream >> keyValue;

			int start = 0;
			int end = keyValue.find(delimiter);
			if (end == std::string::npos)
			{
				delete binding;
				binding = nullptr;
				break;
			}

			EventType type = EventType(stoi(keyValue.substr(start, end - start)));
			int code = stoi(keyValue.substr(end + delimiter.length(), keyValue.find(delimiter, end + delimiter.length())));

			EventInfo eventInfo;
			eventInfo.Code = code;

			binding->BindEvent(type, eventInfo);
		}

		if (!AddBinding(binding))
		{
			delete binding;
		}

		binding = nullptr;
	}

	bindings.close();
}
