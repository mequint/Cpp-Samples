#pragma once

#include "DebugOverlay.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "SharedContext.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Window.h"

class Game {
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	Window* GetWindow();

	sf::Time GetElapsed();
	
private:
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;

	SharedContext m_context;

	// BUG: Window must be above the state manager...this is because of the removal of callbacks in the event manager
	Window m_window;
	EntityManager m_entityManager;
	TextureManager m_textureManager; 
	StateManager m_stateManager;

	DebugOverlay m_debugOverlay;
};