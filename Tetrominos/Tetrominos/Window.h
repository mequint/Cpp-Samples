#pragma once

#include <SFML/Graphics.hpp>

class Window
{
	public:
		Window(const std::string& title, sf::Vector2f& windowSize);
		~Window();

		void Update();

		void SetBackgroundColor(sf::Color color);
		void BeginDraw();
		void EndDraw();

		sf::RenderWindow* GetRenderWindow();

	private:
		sf::RenderWindow m_window;
		sf::Color m_backgroundColor;

		bool m_isDone;
};