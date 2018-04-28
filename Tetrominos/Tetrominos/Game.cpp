#include "Game.h"

#include <iostream>

// Move this to window...
#include <glm/gtc/matrix_transform.hpp>

Game::Game() :
	m_config(),
	m_gameContext(), 
	m_stateManager(&m_gameContext), 
	m_window("Test Program", 800, 600)
{
	setupContext();
}

Game::Game(ConfigurationManager& config) :
	m_config(config),
	m_gameContext(),
	m_stateManager(&m_gameContext),
	m_window(config.Get("AppName"), stoi(config.Get("WindowWidth")), stoi(config.Get("WindowHeight")))
{
	setupContext();
}

Game::~Game() {}

bool Game::Initialize()
{
	// Initialize OpenGL - fail the program if the library isn't loaded... 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	std::string configSetting;

	// Set OpenGL flags
	configSetting = m_config.Get("BlendEnabled");
	if (configSetting != "" && configSetting == "1")
	{
		std::cout << "Blending enabled" << std::endl;;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	m_stateManager.ChangeState(StateType::Intro);
	return true;
}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
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

#pragma region "Helper methods"

void Game::setupContext()
{
	m_gameContext.FontManager = &m_fontManager;
	m_gameContext.ShaderManager = &m_shaderManager;
	m_gameContext.TextureManager = &m_textureManager;
	m_gameContext.Window = &m_window;
}

#pragma endregion