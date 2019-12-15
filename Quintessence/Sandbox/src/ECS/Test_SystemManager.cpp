#include "ECS/Test_SystemManager.h"

#include "ECS/ECSTypes.h"
#include "ECS/Systems/S_Renderer.h"

void Test_SystemManager::draw(qe::Window* window) {
	// Made pure virtual so that rendering can be specialized per game
	auto iter = m_systems.find(static_cast<qe::SystemType>(System::Renderer));
	if (iter == m_systems.end()) return;

	auto renderSystem = dynamic_cast<S_Renderer*>(iter->second.get());
	renderSystem->render(window);
}