#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "EventManager.h"

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void Update();

	void BeginDraw();
	void EndDraw();

	bool IsDone();
	bool IsFullscreen();
	bool IsFocused();

	sf::RenderWindow* GetRenderWindow();
	EventManager* GetEventManager();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen(EventDetails* details);
	void Close(EventDetails* details = nullptr);

private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();

	sf::RenderWindow m_window;
	EventManager m_eventManager;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;

	bool m_isDone;
	bool m_isFullscreen;
	bool m_isFocused;
};