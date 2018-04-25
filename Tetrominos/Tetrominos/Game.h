#pragma once

#include "ConfigurationManager.h"
#include "GameContext.h"
#include "StateManager.h"
#include "Window.h"

#include "FontManager.h"
#include "ShaderManager.h"
#include "Text.h"

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
		ConfigurationManager m_config;
		GameContext m_gameContext;
		StateManager m_stateManager;
		Window m_window;

		// Move to the game context
		ShaderManager m_shaderManager;
		FontManager m_fontManager;

		// Move to a game state...
		Text* m_text;
};