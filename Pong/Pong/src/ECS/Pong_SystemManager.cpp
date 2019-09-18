#include "ECS/Pong_SystemManager.h"

void Pong_SystemManager::Draw(qe::Window * window, unsigned int layer)
{
	auto iter = m_systems.find(System::Renderer);
	if (iter == m_systems.end()) return;

	auto system = dynamic_cast<Sys_Renderer*>(iter->second.get());
	system->Render(window, layer);
}