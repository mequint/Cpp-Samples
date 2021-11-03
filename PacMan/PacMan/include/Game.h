#pragma once

#include "qe/Context.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/State/StateManager.h"
#include "qe/Utilities/RandomGenerator.h"
#include "qe/Window/Window.h"

#include "ECS/PacMan_EntityManager.h"
#include "ECS/PacMan_SystemManager.h"

class Game {
public:
	Game();

	void update();
	void draw();
	void postProcess();

	qe::Window* getWindow();

private:
	qe::Context m_context;

	qe::FontManager m_fontManager;
	qe::RandomGenerator m_random;
	qe::StateManager m_stateManager;
	qe::TextureManager m_textureManager;
	qe::Window m_window;

	PacMan_EntityManager m_entityManager;
	PacMan_SystemManager m_systemManager;

	sf::Clock m_clock;
	sf::Time m_elapsedTime;
};