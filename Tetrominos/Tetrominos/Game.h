#pragma once

#include "ConfigurationManager.h"
#include "Context.h"
#include "StateManager.h"

class Game
{
	public:
		Game();
		Game(ConfigurationManager& config);
		~Game();

		bool Initialize();
		void Update();
		void Render();
		void Cleanup();

		Window* GetWindow();

	private:
		// State
		Context m_context;
		StateManager m_stateManager;

		// Window
		Window m_window;

		// Config
		ConfigurationManager m_config;

		// Managers
		FontManager m_fontManager;
		ShaderManager m_shaderManager;
		TextureManager m_textureManager;

		void setupContext();
};