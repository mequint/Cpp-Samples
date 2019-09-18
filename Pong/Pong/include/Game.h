#pragma once

#include "qe/Context.h"
#include "qe/ECS/Core/EntityManager.h"
#include "ECS/Pong_SystemManager.h"
#include "qe/Resources/AudioManager.h"
#include "qe/Resources/FontManager.h"
#include "qe/Resources/TextureManager.h"
#include "qe/Utilities/RandomGenerator.h"
#include "qe/Sound/SoundManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window//Window.h"

class Game
{
	public:
		Game();
		~Game();

		void Update();
		void Draw();
		void PostProcess();

		sf::Time GetElapsedtime();

		qe::Window* GetWindow();

	private:
		void RestartClock();

		void SetupBindings();
		void SetupECS();
		
		sf::Clock m_clock;
		sf::Time m_elapsedTime;

		qe::Context m_context;
		qe::Window m_window;
		qe::StateManager m_stateManager;
		qe::AudioManager m_audioManager;
		qe::FontManager m_fontManager;
		qe::TextureManager m_textureManager;
		Pong_SystemManager m_systemManager;
		qe::EntityManager m_entityManager;
		qe::RandomGenerator m_randomGenerator;
		qe::SoundManager m_soundManager;
};