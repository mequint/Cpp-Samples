#include "ECS/Systems/S_Collision.h"

#include "qe/ECS/SystemManager.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Collider.h"
#include "ECS/Components/C_Position.h"

S_Collision::S_Collision(qe::SystemManager * systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Collision), systemManager) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Position));
	req.set(static_cast<qe::ComponentType>(Component::Collider));
	m_requiredComponents.push_back(req);
}

void S_Collision::notify(const qe::Message & message) {}

void S_Collision::update(float dt) {
	auto entities = m_systemManager->getEntityManager();

	// Update the positions of the colliders
	for (auto& entity : m_entities) {
		// ...unless the entity is static
		if (!entities->hasComponent(entity, static_cast<qe::ComponentType>(Component::Motion))) continue;

		auto position = entities->getComponent<C_Position>(entity, static_cast<qe::ComponentType>(Component::Position));
		auto collider = entities->getComponent<C_Collider>(entity, static_cast<qe::ComponentType>(Component::Collider));

		collider->setPosition(position->getPosition());
		collider->setColliding(false);
	}

	for (auto iter1 = m_entities.begin(); iter1 != m_entities.end(); ++iter1) {
		// Only check for a collision if the entity in question is dynamic
		if (!entities->hasComponent(*iter1, static_cast<qe::ComponentType>(Component::Motion))) continue;

		for (auto iter2 = std::next(iter1); iter2 != m_entities.end(); ++iter2) {
			auto collider1 = entities->getComponent<C_Collider>(*iter1, static_cast<qe::ComponentType>(Component::Collider));
			auto collider2 = entities->getComponent<C_Collider>(*iter2, static_cast<qe::ComponentType>(Component::Collider));

			if (collider1->getAABB().intersects(collider2->getAABB())) {
				qe::Message message(static_cast<qe::MessageType>(EntityMessage::Collide));
				message.m_sender = *iter1;
				message.m_receiver = *iter2;

				m_systemManager->getMessageDispatch()->dispatch(message);
			}
		}
	}
}

void S_Collision::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}