#pragma once

#include "Window.h"

struct Context
{
	Context() : m_window(nullptr) {}

	Window* m_window;
};