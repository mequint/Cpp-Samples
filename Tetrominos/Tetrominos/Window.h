#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
	public:
		Window();
		Window(const std::string& name, int width, int height, bool fullscreen = false);
		~Window();

		GLFWwindow* GetContext() const;
		bool IsValid() const;

		bool IsDone() const;

		void BeginDraw();
		void EndDraw();

		void Update();

		void ToggleFullscreen();

	private:
		void setup(const std::string& name, int width, int height, bool fullscreen);
		void create();
		void destroy();

		std::string m_name;
		int m_width, m_height;
		bool m_isFullscreen;

		GLFWwindow* m_pWindowContext;
};