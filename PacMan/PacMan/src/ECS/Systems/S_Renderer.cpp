#include "ECS/Systems/S_Renderer.h"

#include "qe/ECS/SystemManager.h"

#include "ECS/Components/C_Position.h"
#include "ECS/Components//C_Sprite.h"

S_Renderer::S_Renderer(qe::SystemManager * systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Renderer), systemManager) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Position));
	req.set(static_cast<qe::ComponentType>(Component::Sprite));
	m_requiredComponents.push_back(req);
}

S_Renderer::~S_Renderer() = default;

void S_Renderer::notify(const qe::Message & message) {}

void S_Renderer::update(float dt) {
	auto entities = m_systemManager->getEntityManager();

	for (auto& entity : m_entities) {
		auto position = entities->getComponent<C_Position>(entity, static_cast<qe::ComponentType>(Component::Position));

		auto drawable = entities->getComponent<C_Drawable>(entity, static_cast<qe::ComponentType>(Component::Sprite));
		drawable->setPosition(position->getPosition());
	}
}

void S_Renderer::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}

void S_Renderer::render(qe::Window * window) {
	auto entities = m_systemManager->getEntityManager();
	auto renderer = window->getRenderWindow();

	for (auto& entity : m_entities) {
		auto drawable = entities->getComponent<C_Drawable>(entity, static_cast<qe::ComponentType>(Component::Sprite));

		drawable->draw(renderer);
	}
}