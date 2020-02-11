#pragma once

#include "qe\ECS\SystemManager.h"
#include "qe\Resource\FontManager.h"
#include "qe\Resource\TextureManager.h"

class PacMan_SystemManager : public qe::SystemManager {
public:
	PacMan_SystemManager(qe::FontManager* fontManager, qe::TextureManager* textureManager, qe::Window* window);

	qe::FontManager* getFontManager();
	qe::TextureManager* getTextureManager();
	qe::Window* getWindow();

	virtual void draw(qe::Window* window) override;

private:
	qe::FontManager* m_fontManager;
	qe::TextureManager* m_textureManager;
	qe::Window* m_window;
};