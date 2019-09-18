#include "ECS/Systems/Sys_Movement.h"

#include "qe/ECS/Core/EntityManager.h"
#include "qe/ECS/Core/SystemManager.h"
#include "qe/Utilities/MathHelpers.h"
#include "qe/Utilities/RandomGenerator.h"

#include "ECS/Components/Comp_Motion.h"
#include "ECS/Components/Comp_Position.h"

Sys_Movement::Sys_Movement(qe::SystemManager* systemManager) : Sys_Base(System::Movement, systemManager) {
	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::Position));
	req.set(static_cast<size_t>(Component::Motion));
	m_requiredComponents.push_back(req);
	req.reset();
}

Sys_Movement::~Sys_Movement() = default;

void Sys_Movement::Update(float dt) {
	auto* entityManager = m_systemManager->GetEntityManager();
	for (auto& entity : m_entities) {
		auto position = entityManager->GetComponent<Comp_Position>(entity, Component::Position);
		auto motion = entityManager->GetComponent<Comp_Motion>(entity, Component::Motion);

		position->Move(motion->GetVelocity() * dt);
	}
}

void Sys_Movement::HandleEvent(const qe::EntityId & entity, const qe::EntityEvent & event) {
	switch (event) {
		case qe::EntityEvent::Collision_X: {
			auto motion = m_systemManager->GetEntityManager()->GetComponent<Comp_Motion>(entity, Component::Motion);

			auto velocity = motion->GetVelocity();
			if (motion->IsBouncy()) {
				velocity.x = -velocity.x;
			}
			else {
				velocity.x = 0;
			}

			motion->SetVelocity(velocity);
			break;
		}

		case qe::EntityEvent::Collision_Y: {
			auto motion = m_systemManager->GetEntityManager()->GetComponent<Comp_Motion>(entity, Component::Motion);
			auto velocity = motion->GetVelocity();

			if (motion->IsBouncy()) {
				velocity.y = -velocity.y;
			}
			else {
				velocity.y = 0;
			}

			motion->SetVelocity(velocity);
			break;
		}
	}
}

void Sys_Movement::Notify(const qe::Message & message) {}