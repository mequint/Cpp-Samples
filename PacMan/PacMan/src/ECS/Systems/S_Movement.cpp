#include "ECS/Systems/S_Movement.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Motion.h"
#include "ECS/Components/C_Position.h"

#include "qe/ECS/SystemManager.h"

S_Movement::S_Movement(qe::SystemManager * systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Movement), systemManager) {
	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Position));
	req.set(static_cast<qe::ComponentType>(Component::Motion));
	m_requiredComponents.push_back(req);
}

S_Movement::~S_Movement() = default;

void S_Movement::notify(const qe::Message & message) {}

void S_Movement::update(float dt) {
	auto entityManager = m_systemManager->getEntityManager();

	for (auto& entity : m_entities) {
		auto position = entityManager->getComponent<C_Position>(entity, static_cast<qe::ComponentType>(Component::Position));
		auto motion = entityManager->getComponent<C_Motion>(entity, static_cast<qe::ComponentType>(Component::Motion));

		position->move(motion->getVelocity() * dt);
	}
}

void S_Movement::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
	auto e = static_cast<EntityEvent>(event);

	switch (e) {
		case EntityEvent::Colliding_X: {
			C_Motion* motion = m_systemManager->getEntityManager()->getComponent<C_Motion>(entityId, static_cast<qe::ComponentType>(Component::Motion));
			motion->setVelocity(0.0f, motion->getVelocity().y);
			break;
		}

		case EntityEvent::Colliding_Y: {
			C_Motion* motion = m_systemManager->getEntityManager()->getComponent<C_Motion>(entityId, static_cast<qe::ComponentType>(Component::Motion));
			motion->setVelocity(motion->getVelocity().x, 0.0f);
			break;
		}
	}
}