#include "qe/Window/Window.h"

namespace qe {
	Window::Window(const std::string& title, const sf::Vector2u& windowSize) :
		m_window(sf::VideoMode(windowSize.x, windowSize.y), title)
	{
		m_windowSize = windowSize;
		m_title = title;
		m_backgroundColor = sf::Color::Black;
		m_isDone = false;

		auto style = sf::Style::Default;
		m_window.create(sf::VideoMode(windowSize.x, windowSize.y, 32), title, style);

		m_eventManager.AddCallback(StateType(0), "CloseWindow", &Window::Close, this);
		m_eventManager.AddCallback(StateType(0), "Key_Escape", &Window::Close, this);
	}

	Window::~Window()
	{
		m_window.close();
	}

	sf::RenderWindow* Window::GetRenderWindow() { return &m_window; }
	EventManager* Window::GetEventManager() { return &m_eventManager; }

	void Window::Close(EventDetails* details)
	{
		m_isDone = true;
	}

	void Window::Update()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			m_eventManager.HandleEvent(event);
		}

		m_eventManager.Update();
	}

	bool Window::IsDone() { return m_isDone; }

	void Window::SetBackgroundColor(sf::Color color) { m_backgroundColor = color; }

	void Window::BeginDraw() { m_window.clear(m_backgroundColor); }
	void Window::EndDraw() { m_window.display(); }
}