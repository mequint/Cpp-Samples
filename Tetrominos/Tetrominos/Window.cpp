#include "Window.h"

#include <GL/glew.h>

Window::Window() :
	Window(WindowSettings(), ProjectorType::Orthographic)
{
}

Window::Window(const WindowSettings & windowSettings, ProjectorType projectorType) :
	m_windowSettings(windowSettings), m_isDone(false), m_pProjector(nullptr)
{
	create();
	m_pProjector = (projectorType == ProjectorType::Orthographic) ? 
		new OrthoProjector(windowSettings.Width, windowSettings.Height) : nullptr;
}

Window::~Window()
{
	delete m_pProjector;
	m_window.close();
}

void Window::BeginDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			m_windowSettings.Focused = false;
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_windowSettings.Focused = true;
		}

		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			toggleFullscreen();
		}
	}
}

bool Window::IsDone() const
{
	return m_isDone;
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &m_window;
}

IProjector* Window::GetProjector()
{
	return m_pProjector;
}

int Window::GetWidth() const
{
	return m_windowSettings.Width;
}

int Window::GetHeight() const
{
	return m_windowSettings.Height;
}

void Window::toggleFullscreen()
{
	m_windowSettings.Fullscreen = !m_windowSettings.Fullscreen;
	m_window.close();
	create();
}

void Window::create()
{
	// Set the OpenGL settings
	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	// Set the Style flags
	sf::Uint32 style = sf::Style::Default;
	if (m_windowSettings.Fullscreen) { style = sf::Style::Fullscreen; }

	m_window.create(sf::VideoMode(m_windowSettings.Width, m_windowSettings.Height, m_windowSettings.BitsPerPixel),
		m_windowSettings.Title, style, settings);
}
