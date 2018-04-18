// GLAD must be on top - otherwise GLFW will throw a fit
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "ConfigurationManager.h"
#include "Shader.h"
#include "Triangle.h"
#include "Window.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

int main()
{
	ConfigurationManager config;
	config.Load("assets/settings.txt");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int windowWidth = stoi(config.Get("WindowWidth"));
	int windowHeight = stoi(config.Get("WindowHeight"));
	std::string appName = config.Get("AppName");

	Window window(appName, windowWidth, windowHeight);
	glfwMakeContextCurrent(window.GetContext());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window.GetContext(), FramebufferSizeCallback);

	// Compile vertex shader
	Shader triangleShader("triangle.vert", "triangle.frag");
	Triangle triangle(triangleShader);

	while (!window.IsDone())
	{
		window.Update();

		// Render
		window.BeginDraw();
		triangle.Draw();
		window.EndDraw();
	}

	glfwTerminate();
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}