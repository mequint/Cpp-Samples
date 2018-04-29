#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <unordered_map>
#include <vector>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MouseButtonDown = sf::Event::MouseButtonPressed,
	MouseButtonUp = sf::Event::MouseButtonReleased,
	MouseScroll = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1,
	Mouse,
	Joystick
};

struct EventInfo
{
	EventInfo() { Code = 0; }
	EventInfo(int event) { Code = event; }

	union
	{
		int Code;
	};
};

struct EventDetails
{
	EventDetails(const std::string& bindingName) : Name(bindingName)
	{
		Clear();
	}

	std::string Name;
	int Width, Height;
	unsigned int TextEntered;
	int MouseX, MouseY;
	int MouseScrollDelta;
	int KeyCode;

	void Clear()
	{
		Width = Height = 0;
		TextEntered = 0;
		MouseX = MouseY = 0;
		MouseScrollDelta = 0;
		KeyCode = -1;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding
{
	Binding(const std::string& name) : Name(name), Details(name), Count(0) {}
	~Binding() {}

	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		Events.emplace_back(type, info);
	}

	Events Events;
	std::string Name;
	int Count;

	EventDetails Details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
	public:
		EventManager();
		~EventManager();

		bool AddBinding(Binding* binding);
		bool RemoveBinding(std::string name);

		void SetCurrentState(StateType stateType);
		void SetFocus(bool focus);

		template <class T>
		bool AddCallback(StateType stateType, const std::string& name, void(T::*func)(EventDetails*), T* instance)
		{
			auto iter = m_callbacks.emplace(stateType, CallbackContainer()).first;
			auto temp = std::bind(func, instance, std::placeholders::_1);

			return iter->second.emplace(name, temp).second;
		}

		bool RemoveCallback(StateType stateType, const std::string& name);

		void HandleEvent(sf::Event& event);
		void Update();

		sf::Vector2i GetMousePosition(sf::RenderWindow* window = nullptr);

	private:
		void loadBindings();

		StateType m_currentState;
		Bindings m_bindings;
		Callbacks m_callbacks;

		bool m_hasFocus;
};