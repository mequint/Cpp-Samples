#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

namespace qe {
	enum class EventType
	{
		Closed = sf::Event::Closed,
		WindowResized = sf::Event::Resized,
		LostFocus = sf::Event::LostFocus,
		GainedFocus = sf::Event::GainedFocus,
		TextEntered = sf::Event::TextEntered,
		KeyDown = sf::Event::KeyPressed,
		KeyUp = sf::Event::KeyReleased,
		MouseWheel = sf::Event::MouseWheelScrolled,
		MButtonDown = sf::Event::MouseButtonPressed,
		MButtonUp = sf::Event::MouseButtonReleased,
		MouseMoved = sf::Event::MouseMoved,
		MouseEntered = sf::Event::MouseEntered,
		MouseLeft = sf::Event::MouseLeft,
		JButtonDown = sf::Event::JoystickButtonPressed,
		JButtonUp = sf::Event::JoystickButtonReleased,
		JoystickMoved = sf::Event::JoystickMoved,
		JoystickConnected = sf::Event::JoystickConnected,
		JoystickDisconnected = sf::Event::JoystickDisconnected,
		Keyboard = sf::Event::Count + 1,
		Mouse,
		Joystick
	};

	struct EventInfo
	{
		EventInfo() { m_code = 0; }
		EventInfo(int event) { m_code = event; }

		union
		{
			int m_code;
		};
	};

	using Events = std::vector<std::pair<EventType, EventInfo>>;

	struct EventDetails
	{
		EventDetails(const std::string& binding) : m_name(binding)
		{
			Clear();
		}

		void Clear()
		{
			m_size = sf::Vector2i(0, 0);
			m_textEntered = 0;
			m_mouse = sf::Vector2i(0, 0);
			m_mouseWheelDelta = 0;
			m_keyCode = -1;
		}

		std::string m_name;

		sf::Vector2i m_size;
		sf::Uint32 m_textEntered;
		sf::Vector2i m_mouse;
		sf::Vector2f m_joystickXY;
		int m_mouseWheelDelta;
		int m_keyCode;
	};

	struct Binding
	{
		Binding(const std::string& name) : m_name(name), m_details(name), m_count(0)
		{}

		~Binding() {}

		void BindEvent(EventType type, EventInfo info = EventInfo())
		{
			m_events.emplace_back(type, info);
		}

		Events m_events;
		std::string m_name;
		int m_count;

		EventDetails m_details;
	};

	using Bindings = std::unordered_map<std::string, Binding*>;
	using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

	enum class StateType;
	using Callbacks = std::unordered_map<StateType, CallbackContainer>;


	class EventManager
	{
		public:
			EventManager(bool loadFromFile = false);
			~EventManager();

			bool AddBinding(const std::string& m_name, int eventType, int code);
			bool AddBinding(Binding* binding);
			bool RemoveBinding(std::string name);

			void SetCurrentState(StateType state);
			void SetFocus(bool focus);

			template <class T>
			bool AddCallback(StateType state, const std::string& name, void(T::*func)(EventDetails*), T* instance)
			{
				auto iter = m_callbacks.emplace(state, CallbackContainer()).first;
				auto temp = std::bind(func, instance, std::placeholders::_1);
				return iter->second.emplace(name, temp).second;
			}

			bool RemoveCallback(StateType state, const std::string& name);

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
}