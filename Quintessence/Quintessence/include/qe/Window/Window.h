#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Cursor.h"

namespace qe {
	// Handles the event handling and display of a window
	class Window {
		public:
			// Window constructor takes application title, window height, and window width
			Window(const std::string& title, unsigned int width, unsigned int height);
			// Window constructor takes application title and window size as a 2d vector
			Window(const std::string& title, const sf::Vector2u& windowSize);

			// Deconstructor
			~Window();

			// Sets the color the window will clear to
			void setBackgroundColor(const sf::Color& color);

			// Loads a cursor with a user defined filename and hotspot
			void setCursor(const std::string& filename, const sf::Vector2u& hotspot);
			// Loads a System pre-defined cursor
			void setCursor(const CursorType& type);

			// Begins the current draw frame
			void beginDraw();

			// Ends the draw frame and presents it to the screen
			void endDraw();

			// Polls for events
			void update();

			// Flag that the window is no longer needed
			bool isDone();

			// Get the underlying rendering window
			sf::RenderWindow* getRenderWindow();

			// Tells the window it is no longer needed
			void close();

	private:
		// Creates the underlying render window
		void _create();

		sf::RenderWindow m_window;

		sf::Vector2u m_windowSize;
		std::string m_title;
		sf::Color m_backgroundColor;

		bool m_isDone;
		bool m_isFullscreen;
		bool m_hasFocus;
	};
}