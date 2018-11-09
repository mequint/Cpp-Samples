#pragma once

#include "EventManager.h"
#include "FontManager.h"
#include "GameData.h"
#include "Window.h"

struct Context
{
	Context() : m_eventManager(nullptr), m_fontManager(nullptr), m_window(nullptr) {}

	EventManager* m_eventManager;
	FontManager* m_fontManager;
	GameData* m_gameData;
	Window* m_window;
};