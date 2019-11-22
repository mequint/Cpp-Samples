#pragma once

class DebugOverlay;
class EntityManager;
class EventManager;
class Map;
class TextureManager;
class Window;

struct SharedContext {
	SharedContext() :
		m_window(nullptr),
		m_eventManager(nullptr),
		m_textureManager(nullptr),
		m_entityManager(nullptr),
		m_gameMap(nullptr),
		m_debugOverlay(nullptr) {
	}

	Window* m_window;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	EntityManager* m_entityManager;
	Map* m_gameMap;
	DebugOverlay* m_debugOverlay;
};