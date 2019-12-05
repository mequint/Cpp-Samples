#pragma once

#include "qe/Context.h"
#include "qe/Resource/TextureManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

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

	qe::StateManager m_stateManager;
	qe::TextureManager m_textureManager;
	qe::Window m_window;

	qe::Context m_context;
};