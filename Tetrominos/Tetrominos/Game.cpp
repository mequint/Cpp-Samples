#include "Game.h"

#include <GL/glew.h>
#include <iostream>

Game::Game() :
	m_window(WindowSettings()),
	m_context(),
	m_stateManager(&m_context)
{
	setupContext();
}

Game::Game(ConfigurationManager & config) :
	m_config(config),
	m_context(),
	m_stateManager(&m_context),
	m_window(
		WindowSettings(
			config.Get("AppName"),
			stoi(config.Get("WindowWidth")),
			stoi(config.Get("WindowHeight")),
			stoi(config.Get("BitsPerPixel"))
		))
{
	setupContext();
}

Game::~Game() {}

bool Game::Initialize()
{
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "<Game::Initialize>: Failed to initialize GLEW" << std::endl;
		return false;
	}

	std::string configSetting;

	// Set OpenGL flags
	configSetting = m_config.Get("BlendEnabled");
	if (configSetting != "" && configSetting == "1")
	{
		std::cout << "Blending enabled" << std::endl;
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
}

Window* Game::GetWindow()
{
	return &m_window;
}

#pragma region "Helper methods"

void Game::setupContext()
{
	m_context.FontManager = &m_fontManager;
	m_context.ShaderManager = &m_shaderManager;
	m_context.TextureManager = &m_textureManager;
	m_context.Window = &m_window;
}

#pragma endregion