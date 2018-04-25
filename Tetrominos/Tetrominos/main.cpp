// GLAD must be on top - otherwise GLFW will throw a fit
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "ConfigurationManager.h"
#include "FontManager.h"
#include "ShaderManager.h"

#include "Text.h"
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 ortho = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);

	// Compile vertex shader
	ShaderManager shaderManager;
	Shader textShader = shaderManager.LoadShader("text", "Assets/shaders/text.vert", "Assets/shaders/text.frag");
	textShader.Use();
	textShader.Set("projection", ortho);

	// Load font
	FontManager fontManager;
	fontManager.Load("Assets/fonts/arial.ttf", "arial", 24);
	Font font = fontManager.GetFont("arial");

	Text text(textShader, font, "Hello OpenGL!!!");
	text.SetPosition(100.0f, 100.0f);

	while (!window.IsDone())
	{
		window.Update();

		// Render
		window.BeginDraw();
		text.Draw();
		window.EndDraw();
	}

	glfwTerminate();
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}