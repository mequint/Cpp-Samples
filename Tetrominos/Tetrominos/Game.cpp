#include "Game.h"

#include <iostream>

// Move this to window...
#include <glm/gtc/matrix_transform.hpp>

Game::Game() :
	m_config(),
	m_gameContext(), 
	m_stateManager(&m_gameContext), 
	m_window("Test Program", 800, 600),
	m_text(nullptr)
{
}

Game::Game(ConfigurationManager& config) :
	m_config(config),
	m_gameContext(),
	m_stateManager(&m_gameContext),
	m_window(config.Get("AppName"), stoi(config.Get("WindowWidth")), stoi(config.Get("WindowHeight")))
{
}

Game::~Game() 
{
	delete m_text;
}

bool Game::Initialize()
{
	// Initialize OpenGL - fail the program if the 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	std::string configSetting;
	configSetting = m_config.Get("BlendEnabled");
	if (configSetting != "" && configSetting == "1")
	{
		std::cout << "Blending enabled" << std::endl;;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Load the game objects here...
// TODO: Move this to the window class, then to a Projector class (needs to be created)
	const int WindowWidth = stoi(m_config.Get("WindowWidth"));
	const int WindowHeight = stoi(m_config.Get("WindowHeight"));
	glm::mat4 ortho = glm::ortho(0.f, static_cast<float>(WindowWidth), static_cast<float>(WindowHeight), 0.0f, -1.0f, 1.0f);

// Move this functionality into a specific state
	// Load shader
	Shader textShader = m_shaderManager.LoadShader("text", "Assets/shaders/text.vert", "Assets/shaders/text.frag");
	textShader.Use();
	textShader.Set("projection", ortho);	// Get from the window projector

	// Load font
	m_fontManager.Load("Assets/fonts/arial.ttf", "arial24", 24);
	Font font = m_fontManager.GetFont("arial24");

	// Create text object (make a builder for this...)
	m_text = new Text(textShader, font, "Hello OpenGL!!!");
	m_text->SetPosition(100.0f, 100.0f);

	return true;
}

void Game::Update()
{
	m_window.Update();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_text->Draw();
	m_window.EndDraw();
}

void Game::Cleanup()
{
	glfwTerminate();
}

Window * Game::GetWindow()
{
	return &m_window;
}