#include "ECS/PacMan_SystemManager.h"

#include "ECS/ECS_Types.h"
#include "ECS/Systems/S_GameUI.h"
#include "ECS/Systems/S_Renderer.h"

PacMan_SystemManager::PacMan_SystemManager(qe::FontManager * fontManager, qe::TextureManager * textureManager, qe::Window* window) :
	m_fontManager(fontManager),
	m_textureManager(textureManager),
	m_window(window) {
}

qe::FontManager * PacMan_SystemManager::getFontManager() {
	return m_fontManager;
}

qe::TextureManager * PacMan_SystemManager::getTextureManager() {
	return m_textureManager;
}

qe::Window * PacMan_SystemManager::getWindow() {
	return m_window;
}

void PacMan_SystemManager::draw(qe::Window * window) {
	auto iter = m_systems.find(static_cast<qe::SystemType>(System::Renderer));
	if (iter != m_systems.end()) {
		auto renderSystem = dynamic_cast<S_Renderer*>(iter->second.get());
		renderSystem->render(window);
	}

	iter = m_systems.find(static_cast<qe::SystemType>(System::GameUI));
	if (iter != m_systems.end()) {
		auto ui = dynamic_cast<S_GameUI*>(iter->second.get());
		ui->render(window);
	}
}