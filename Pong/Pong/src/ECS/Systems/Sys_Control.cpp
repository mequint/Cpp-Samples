#include "ECS/Systems/Sys_Control.h"

#include "qe/ECS/Core/SystemManager.h"

#include "ECS/Components/Comp_Motion.h"
#include "ECS/Components/Comp_Position.h"

Sys_Control::Sys_Control(qe::SystemManager * systemManager) : Sys_Base(System::Control, systemManager) {
	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::Motion));
	req.set(static_cast<size_t>(Component::Controller));
	m_requiredComponents.push_back(req);

	req.reset();
}

Sys_Control::~Sys_Control() = default;

void Sys_Control::Update(float dt) {
}

void Sys_Control::HandleEvent(const qe::EntityId & entityId, const qe::EntityEvent& event) {
	auto entityManager = m_systemManager->GetEntityManager();

	auto motion = entityManager->GetComponent<Comp_Motion>(entityId, Component::Motion);

	switch (event) {
		case qe::EntityEvent::Moving_Up:
			motion->SetVelocity(sf::Vector2f(0.0f, -128.0f));
			break;

		case qe::EntityEvent::Moving_Down:
			motion->SetVelocity(sf::Vector2f(0.0f, 128.0f));
			break;

		case qe::EntityEvent::Stop:
			motion->SetVelocity(sf::Vector2f(0.0f, 0.0f));
			break;
	}
}

void Sys_Control::Notify(const qe::Message & message) {}