#include "Window.h"

#include <GL/glew.h>

Window::Window() :
	Window(WindowSettings(), ProjectorType::Orthographic)
{
}

Window::Window(const WindowSettings & windowSettings, ProjectorType projectorType) :
	m_windowSettings(windowSettings), m_isDone(false), m_pProjector(nullptr)
{
	//m_eventManager.AddCallback(StateType(0), "ToggleFullscreen", &Window::toggleFullscreen, this);
	m_eventManager.AddCallback(StateType(0), "CloseWindow", &Window::close, this);
	m_eventManager.AddCallback(StateType(0), "EscapeKey", &Window::close, this);

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
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_windowSettings.Focused = true;
			m_eventManager.SetFocus(true);
		}

		m_eventManager.HandleEvent(event);
	}

	m_eventManager.Update();
}

bool Window::IsDone() const
{
	return m_isDone;
}

bool Window::IsFullscreen() const
{
	return m_windowSettings.Fullscreen;
}

bool Window::HasFocus() const
{
	return m_windowSettings.Focused;
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &m_window;
}

EventManager* Window::GetEventManager()
{
	return &m_eventManager;
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

void Window::close(EventDetails* details)
{
	m_isDone = true;
}

void Window::toggleFullscreen(EventDetails* details)
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
	if (m_windowSettings.Fullscreen)
	{
		m_window.create(sf::VideoMode::getFullscreenModes()[0], m_windowSettings.Title, sf::Style::Fullscreen, settings);
	}
	else
	{
		m_window.create(sf::VideoMode(m_windowSettings.Width, m_windowSettings.Height, m_windowSettings.BitsPerPixel),
			m_windowSettings.Title, sf::Style::Default, settings);
	}

}