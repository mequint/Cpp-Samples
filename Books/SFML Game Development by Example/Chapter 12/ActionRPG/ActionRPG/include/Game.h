#pragma once

#include "AudioManager.h"
#include "DebugOverlay.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "FontManager.h"
#include "GUI_Manager.h"
#include "SharedContext.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "SystemManager.h"
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

	// BUG: Window must be above the state manager...this is because the removal of callbacks occurs when the event manager is destroyed
	Window m_window;
	TextureManager m_textureManager;
	FontManager m_fontManager;
	AudioManager m_audioManager;
	SoundManager m_soundManager;
	SystemManager m_systemManager;
	EntityManager m_entityManager;
	GUI_Manager m_guiManager;
	StateManager m_stateManager;

	DebugOverlay m_debugOverlay;
};