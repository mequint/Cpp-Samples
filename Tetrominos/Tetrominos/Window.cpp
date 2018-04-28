#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window() : m_pProjector(nullptr)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	setup("Test Window", 800, 600, ProjectorType::Orthographic, false);
	glfwMakeContextCurrent(m_pWindowContext);
}

Window::Window(const std::string & name, int width, int height, ProjectorType projectorType, bool fullscreen)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	setup(name, width, height, projectorType, fullscreen);
}

Window::~Window()
{
	destroy();
}

GLFWwindow* Window::GetContext() const
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
		toggleFullscreen();
	}
}

IProjector* Window::GetProjector()
{
	return m_pProjector;
}

int Window::GetWidth() const	{ return m_width; }
int Window::GetHeight() const	{ return m_height; }

void Window::toggleFullscreen()
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

void Window::setup(const std::string & name, int width, int height, ProjectorType projectorType, bool fullscreen)
{
	m_name = name;
	m_width = width;
	m_height = height;
	m_isFullscreen = fullscreen;

	create();

	m_pProjector = (projectorType == ProjectorType::Orthographic) ? new OrthoProjector(width, height) : nullptr;
}

void Window::create()
{
	auto monitor = (m_isFullscreen) ? glfwGetPrimaryMonitor() : nullptr;

	m_pWindowContext = glfwCreateWindow(m_width, m_height, m_name.c_str(), monitor, nullptr);
	if (nullptr == m_pWindowContext)
	{
		std::cout << "<Window>: Failed to create the GLFW window" << std::endl;
	}

	glfwMakeContextCurrent(m_pWindowContext);

	glfwSetFramebufferSizeCallback(m_pWindowContext, Window::resizeCallback);
}

void Window::destroy()
{
	glfwDestroyWindow(m_pWindowContext);
}

#pragma region "Static callback methods..."

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

#pragma endregion