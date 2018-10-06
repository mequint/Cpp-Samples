#include "Window.h"

Window::Window(const std::string& title, sf::Vector2f& windowSize) :
	m_window(sf::VideoMode(windowSize.x, windowSize.y), title)
{
	m_isDone = false;

	m_backgroundColor = sf::Color::Black;

	auto style = sf::Style::Default;

	m_window.create(sf::VideoMode(windowSize.x, windowSize.y, 32), title, style);
}

Window::~Window()
{
	m_window.close();
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &m_window;
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
	}
}

void Window::SetBackgroundColor(sf::Color color)
{
	m_backgroundColor = color;
}

void Window::BeginDraw()
{
	m_window.clear(m_backgroundColor);
}

void Window::EndDraw()
{
	m_window.display();
}
