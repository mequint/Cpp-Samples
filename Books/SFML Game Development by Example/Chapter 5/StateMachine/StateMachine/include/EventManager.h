#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
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

struct EventInfo {
	EventInfo() { m_code = 0; }
	EventInfo(int event) { m_code = event; }

	union {
		int m_code;
	};
};

struct EventDetails {
	EventDetails(const std::string& bindName) : 
		m_name(bindName) {
		Clear();
	}

	std::string m_name;	

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void Clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding {
	Binding(const std::string& name) : m_name(name), m_details(name), c(0) {}
	~Binding() = default;

	void BindEvent(EventType type, EventInfo info = EventInfo()) {
		m_events.emplace_back(type, info);
	}

	Events m_events;
	std::string m_name;
	int c;

	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager {
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* binding);
	bool RemoveBinding(const std::string& name);

	void SetCurrentState(const StateType& state);
	void SetFocus(bool focus);

	template <class T>
	bool AddCallback(const StateType& state, const std::string& name, void (T::*func)(EventDetails*), T* instance) {
		auto iter = m_callbacks.emplace(state, CallbackContainer()).first;
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return iter->second.emplace(name, temp).second;
	}

	bool RemoveCallback(const StateType& state, const std::string& name) {
		auto iter = m_callbacks.find(state);
		if (iter == m_callbacks.end()) return false;

		auto iter2 = iter->second.find(name);
		if (iter2 == iter->second.end()) return false;

		iter->second.erase(name);
		return true;
	}

	void HandleEvent(sf::Event& event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* window = nullptr);

private:
	void LoadBindings();

	StateType m_currentState;
	Bindings m_bindings;
	Callbacks m_callbacks;
	
	bool m_hasFocus;
};