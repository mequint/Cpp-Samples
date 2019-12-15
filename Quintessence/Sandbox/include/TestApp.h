#pragma once

#include "qe/Context.h"
#include "qe/Resource/FontManager.h"
#include "qe/Resource/TextureManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

#include "ECS/Test_EntityManager.h"
#include "ECS/Test_SystemManager.h"

class TestApp {
public:
	TestApp();

	void update();
	void draw();
	void postProcess();

	qe::Window* getWindow();

private:
	sf::Clock m_clock;
	sf::Time m_elapsedTime;

	
	qe::FontManager m_fontManager;
	qe::StateManager m_stateManager;
	qe::TextureManager m_textureManager;
	qe::Window m_window;

	Test_EntityManager m_entityManager;
	Test_SystemManager m_systemManager;

	qe::Context m_context;
};