#include "ECS/Systems/S_State.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_EntityType.h"
#include "Utilities/Directions.h"

#include "qe/ECS/SystemManager.h"

S_State::S_State(qe::SystemManager * systemManager) : 
	S_Base(static_cast<qe::SystemType>(System::State), systemManager) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::EntityType));
	req.set(static_cast<qe::ComponentType>(Component::State));
	m_requiredComponents.push_back(req);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::Collide), this);
}

S_State::~S_State() = default;

void S_State::notify(const qe::Message & message) {
	auto entities = m_systemManager->getEntityManager();

	auto msg = static_cast<EntityMessage>(message.m_type);

	switch (msg) {
		case EntityMessage::Collide: {
			auto entityType1 = entities->getComponent<C_EntityType>(message.m_sender, static_cast<qe::ComponentType>(Component::EntityType));
			auto entityType2 = entities->getComponent<C_EntityType>(message.m_receiver, static_cast<qe::ComponentType>(Component::EntityType));

			if (entityType1->getEntityType() == EntityType::PacMan) {
				if (entityType2->getEntityType() == EntityType::Dot || entityType2->getEntityType() == EntityType::Pill) {
					m_systemManager->addEvent(message.m_receiver, static_cast<qe::EntityEventType>(EntityEvent::Remove));
				}
			}
			break;
		}
	}
}

void S_State::update(float dt) {}

void S_State::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
	auto entities = m_systemManager->getEntityManager();

	switch (static_cast<EntityEvent>(event)) {
		case EntityEvent::Remove:
			entities->removeEntity(entityId);
			break;
	}
}

void S_State::_changeState(const qe::EntityId & entityId, const EntityState & entityState) {}