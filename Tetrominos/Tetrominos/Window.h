#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Projector.h"

class Window
{
	public:
		Window();
		Window(const std::string& name, int width, int height, ProjectorType projectorType = ProjectorType::Orthographic, bool fullscreen = false);
		~Window();

		GLFWwindow* GetContext() const;
		bool IsValid() const;

		bool IsDone() const;

		void BeginDraw();
		void EndDraw();

		void Update();

		IProjector* GetProjector();
		int GetWidth() const;
		int GetHeight() const;

	private:
		void toggleFullscreen();

		void setup(const std::string& name, int width, int height, ProjectorType projectorType, bool fullscreen);
		void create();
		void destroy();

		std::string m_name;
		int m_width, m_height;
		bool m_isFullscreen;

		GLFWwindow* m_pWindowContext;
		IProjector* m_pProjector;

		// Callbacks - GLFW requires this to be static...stupid C...
		static void resizeCallback(GLFWwindow* window, int width, int height);
};