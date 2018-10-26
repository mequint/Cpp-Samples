#pragma once

#include "EventManager.h"
#include "Window.h"

struct Context
{
	Context() : m_eventManager(nullptr), m_window(nullptr) {}

	EventManager* m_eventManager;
	Window* m_window;
};