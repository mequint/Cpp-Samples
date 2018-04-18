#include "Window.h"

#include <iostream>

Window::Window()
{
	setup("Test Window", 800, 600, false);
}

Window::Window(const std::string & name, int width, int height, bool fullscreen)
{
	setup(name, width, height, fullscreen);
}

Window::~Window()
{
	destroy();
}

GLFWwindow * Window::GetContext() const
{
	return m_pWindowContext;
}

bool Window::IsValid() const
{
	return m_pWindowContext != nullptr;
}

bool Window::IsDone() const
{
	return glfwWindowShouldClose(m_pWindowContext);
}

void Window::BeginDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndDraw()
{
	glfwSwapBuffers(m_pWindowContext);
}

void Window::Update()
{
	glfwPollEvents();

	if (glfwGetKey(m_pWindowContext, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_pWindowContext, true);
	}

	if (glfwGetKey(m_pWindowContext, GLFW_KEY_F5) == GLFW_PRESS)
	{
		ToggleFullscreen();
	}
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	if (m_isFullscreen)
	{
		glfwSetWindowMonitor(m_pWindowContext, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(m_pWindowContext, nullptr, 200, 200, m_width, m_height, mode->refreshRate);
	}
}

void Window::setup(const std::string & name, int width, int height, bool fullscreen)
{
	m_name = name;
	m_width = width;
	m_height = height;
	m_isFullscreen = fullscreen;

	create();
}

void Window::create()
{
	auto monitor = (m_isFullscreen) ? glfwGetPrimaryMonitor() : nullptr;

	m_pWindowContext = glfwCreateWindow(m_width, m_height, m_name.c_str(), monitor, nullptr);
	if (nullptr == m_pWindowContext)
	{
		std::cout << "<Window>: Failed to create the GLFW window" << std::endl;
	}
}

void Window::destroy()
{
	glfwDestroyWindow(m_pWindowContext);
}