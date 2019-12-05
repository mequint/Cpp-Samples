#pragma once

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace qe {
	struct EventDetails {
		EventDetails(const std::string& bindingName) :
			m_name(bindingName) {

			clear();
		}

		std::string m_name;

		sf::Vector2i m_size;
		sf::Uint32 m_textEntered;
		sf::Vector2i m_mouse;
		int m_mouseWheelDelta;
		int m_keyCode;
	
		bool m_controlPressed;
		bool m_altPressed;
		bool m_shiftPressed;
		bool m_systemPressed;

		void clear() {
			m_size = sf::Vector2i(0, 0);
			m_textEntered = 0;
			m_mouse = sf::Vector2i(0, 0);
			m_mouseWheelDelta = 0;
			m_keyCode = -1;
		}
	};
}