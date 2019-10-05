#include "ECS/Pong_SystemManager.h"

void Pong_SystemManager::Draw(qe::Window * window, unsigned int layer)
{
	auto iter = m_systems.find(System::Renderer);
	if (iter == m_systems.end()) return;

	auto renderSystem = dynamic_cast<Sys_Renderer*>(iter->second.get());
	renderSystem->Render(window, layer);

	iter = m_systems.find(System::HUD);
	if (iter == m_systems.end()) return;

	auto hudSystem = dynamic_cast<Sys_HUD*>(iter->second.get());
	hudSystem->Render(window, layer);
}