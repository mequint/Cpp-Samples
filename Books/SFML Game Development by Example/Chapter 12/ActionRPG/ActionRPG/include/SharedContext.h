#pragma once

class AudioManager;
class DebugOverlay;
class EntityManager;
class EventManager;
class FontManager;
class GUI_Manager;
class Map;
class SoundManager;
class SystemManager;
class TextureManager;
class Window;

struct SharedContext {
	SharedContext() :
		m_window(nullptr),
		m_eventManager(nullptr),
		m_textureManager(nullptr),
		m_fontManager(nullptr),
		m_audioManager(nullptr),
		m_soundManager(nullptr),
		m_systemManager(nullptr),
		m_entityManager(nullptr),
		m_gameMap(nullptr),
		m_guiManager(nullptr),
		m_debugOverlay(nullptr) {
	}

	Window* m_window;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	FontManager* m_fontManager;
	AudioManager* m_audioManager;
	SoundManager* m_soundManager;
	SystemManager* m_systemManager;
	EntityManager* m_entityManager;
	Map* m_gameMap;
	GUI_Manager* m_guiManager;
	DebugOverlay* m_debugOverlay;
};