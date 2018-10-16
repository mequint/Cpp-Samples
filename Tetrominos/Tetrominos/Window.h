#pragma once

#include <SFML/Graphics.hpp>

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

		void Close();

	private:
		sf::RenderWindow m_window;

		sf::Vector2u m_windowSize;
		std::string m_title;
		sf::Color m_backgroundColor;

		bool m_isDone;
};