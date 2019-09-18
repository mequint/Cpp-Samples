#include "ECS/Systems/Sys_Renderer.h"

#include "qe/ECS/Core/SystemManager.h"

#include "ECS/Components/Comp_Position.h"
#include "ECS/Components/Comp_Sprite.h"

Sys_Renderer::Sys_Renderer(qe::SystemManager * systemManager) : 
	Sys_Base(System::Renderer, systemManager) {

	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::Position));
	req.set(static_cast<size_t>(Component::Sprite));
	m_requiredComponents.push_back(req);

	req.reset(static_cast<size_t>(Component::Sprite));
	req.set(static_cast<size_t>(Component::Text));
	m_requiredComponents.push_back(req);

	m_drawableTypes.set(static_cast<size_t>(Component::Sprite));
	m_drawableTypes.set(static_cast<size_t>(Component::Text));
}

Sys_Renderer::~Sys_Renderer() = default;

void Sys_Renderer::Update(float dt) {
	auto entities = m_systemManager->GetEntityManager();
	for (auto& entity : m_entities) {
		auto position = entities->GetComponent<Comp_Position>(entity, Component::Position);

		Comp_Drawable* drawable = GetDrawableFromType(entity);
		if (!drawable) continue;

		drawable->SetPosition(position->GetPosition());
	}
}

void Sys_Renderer::HandleEvent(const qe::EntityId & entity, const qe::EntityEvent & event) {
	if (event == qe::EntityEvent::Moving) {
		// Sort Drawables...
	}
}

void Sys_Renderer::Notify(const qe::Message & message) {
}

void Sys_Renderer::Render(qe::Window * window, unsigned int layer) {
	auto entities = m_systemManager->GetEntityManager();
	auto renderWindow = window->GetRenderWindow();

	for (auto& entity : m_entities) {
		Comp_Drawable* drawable = GetDrawableFromType(entity);
		if (!drawable) continue;

		drawable->Draw(renderWindow);
	}
}

Comp_Drawable * Sys_Renderer::GetDrawableFromType(const qe::EntityId & entityId) {
	auto entities = m_systemManager->GetEntityManager();

	for (size_t i = 0; i < static_cast<size_t>(Component::COUNT); ++i) {
		if (!m_drawableTypes[i]) continue;

		auto component = static_cast<Component>(i);
		if (!entities->HasComponent(entityId, component)) continue;

		return entities->GetComponent<Comp_Drawable>(entityId, component);
	}

	return nullptr;
}