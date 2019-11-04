#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void Update();

	void BeginDraw();
	void Draw(sf::Drawable& drawable);
	void EndDraw();

	bool IsDone();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};