#pragma once

#include "FontManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Window.h"

struct Context
{
	Context() :
		FontManager(nullptr),
		ShaderManager(nullptr),
		TextureManager(nullptr),
		Window(nullptr)
	{}

	FontManager* FontManager;
	ShaderManager* ShaderManager;
	TextureManager* TextureManager;
	Window* Window;
};