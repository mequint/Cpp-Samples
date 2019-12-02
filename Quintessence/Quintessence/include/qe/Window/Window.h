#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Cursor.h"
#include "EventManager.h"

namespace qe {
	class Window {
		public:
			Window(const std::string& title, unsigned int width, unsigned int height);
			Window(const std::string& title, const sf::Vector2u& windowSize);

			~Window();

			void setBackgroundColor(const sf::Color& color);

			void setCursor(const std::string& filename, const sf::Vector2u& hotspot);
			void setCursor(const CursorType& type);

			void beginDraw();
			void endDraw();

			void update();

			bool isDone();

			sf::RenderWindow* getRenderWindow();

			void close(EventDetails* details);
			void onClick(EventDetails* details);

			EventManager* getEventManager();
			void setEventManager(const EventManager& eventManager);

	private:
		void _create();

		sf::RenderWindow m_window;
		EventManager m_eventManager;

		sf::Vector2u m_windowSize;
		std::string m_title;
		sf::Color m_backgroundColor;

		bool m_isDone;
		bool m_isFullscreen;
		bool m_hasFocus;
	};
}