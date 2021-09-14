#pragma once

#include <SFML/Window/Event.hpp>

namespace qe {
	enum class EventType {
		Closed = sf::Event::Closed,
		WindowResized = sf::Event::Resized,
		LostFocus = sf::Event::LostFocus,
		GainedFocus = sf::Event::GainedFocus,
		TextEntered = sf::Event::TextEntered,
		KeyDown = sf::Event::KeyPressed,
		KeyUp = sf::Event::KeyReleased,
		MouseWheel = sf::Event::MouseWheelMoved,
		MButtonDown = sf::Event::MouseButtonPressed,
		MButtonUp = sf::Event::MouseButtonReleased,
		MouseEntered = sf::Event::MouseEntered,
		MouseLeft = sf::Event::MouseLeft,
		Keyboard = sf::Event::Count + 1,
		Mouse,
		Joystick
	};
}