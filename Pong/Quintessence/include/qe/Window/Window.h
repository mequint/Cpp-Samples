#pragma once

#include <SFML/Graphics.hpp>

#include "qe/Event/EventManager.h"

namespace qe {
	class Window
	{
		public:
			Window(const std::string& title, const sf::Vector2u& windowSize);
			~Window();

			void SetBackgroundColor(sf::Color color);
			void BeginDraw();
			void EndDraw();
		
			void Update();

			bool IsDone();

			sf::RenderWindow* GetRenderWindow();
			EventManager* GetEventManager();

			void Close(EventDetails* details);

		private:
			sf::RenderWindow m_window;
			EventManager m_eventManager;

			sf::Vector2u m_windowSize;
			std::string m_title;
			sf::Color m_backgroundColor;

			bool m_isDone;
	};
}