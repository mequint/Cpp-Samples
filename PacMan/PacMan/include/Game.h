#pragma once

#include "qe/Context.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

class Game {
public:
	Game();

	void update();
	void draw();
	void postProcess();

	qe::Window* getWindow();

private:
	qe::Context m_context;

	qe::StateManager m_stateManager;
	qe::Window m_window;

	sf::Clock m_clock;
	sf::Time m_elapsedTime;
};