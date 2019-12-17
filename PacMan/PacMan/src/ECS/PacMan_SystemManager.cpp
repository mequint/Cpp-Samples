#include "ECS/PacMan_SystemManager.h"

#include "ECS/ECS_Types.h"
#include "ECS/Systems/S_Renderer.h"

void PacMan_SystemManager::draw(qe::Window * window) {
	auto iter = m_systems.find(static_cast<qe::SystemType>(System::Renderer));
	if (iter == m_systems.end()) return;

	auto renderSystem = dynamic_cast<S_Renderer*>(iter->second.get());
	renderSystem->render(window);
}