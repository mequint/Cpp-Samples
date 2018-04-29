#pragma once

#include "EventManager.h"
#include "FontManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Window.h"

struct Context
{
	Context() :
		EventManager(nullptr),
		FontManager(nullptr),
		ShaderManager(nullptr),
		TextureManager(nullptr),
		Window(nullptr)
	{}

	EventManager* EventManager;
	FontManager* FontManager;
	ShaderManager* ShaderManager;
	TextureManager* TextureManager;
	Window* Window;
};