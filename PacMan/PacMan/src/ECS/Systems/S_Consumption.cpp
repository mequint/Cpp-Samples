#include "ECS/Systems/S_Consumption.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_EntityType.h"
#include "qe/ECS/SystemManager.h"

S_Consumption::S_Consumption(qe::SystemManager* systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Consumption), systemManager) {

	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::Consumable));
	bits.set(static_cast<qe::ComponentType>(Component::EntityType));
	m_requiredComponents.push_back(bits);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::Collide), this);
}

void S_Consumption::notify(const qe::Message& message) {
	auto entities = m_systemManager->getEntityManager();

	auto msg = static_cast<EntityMessage>(message.m_type);

	switch (msg) {
		case EntityMessage::Collide: {
			qe::Message scoreMessage(static_cast<qe::MessageType>(EntityMessage::UpdateScore));
			scoreMessage.m_sender = message.m_receiver;
			m_systemManager->getMessageDispatch()->dispatch(scoreMessage);

			m_systemManager->addEvent(message.m_receiver, static_cast<qe::EntityEventType>(EntityEvent::Remove));
			break;
		}
	}
}

void S_Consumption::update(float dt) {
	// Some events need to happen after a certain number of consumables have been consumed
	auto entities = m_systemManager->getEntityManager();

	// Get the count of dots and pills - ignore the fruit (which would be the last item in the array if it exists)
	int dotsRemaining = static_cast<int>(m_entities.size());
	if (dotsRemaining) {
		auto backEntityType = entities->getComponent<C_EntityType>(m_entities.back(), static_cast<qe::ComponentType>(Component::EntityType));
		if (backEntityType->getEntityType() == EntityType::Fruit) {
			dotsRemaining--;
		}
	}

	// May want to invert this, since levels may not have the same number of dots...
	// Fruits should appear after Pac Man consumes 70 dots and 170 dots
	if (dotsRemaining == 174 || dotsRemaining == 74) {
		// Spawn fruit!
	}
	else if (dotsRemaining == 0) {
		qe::Message msg(static_cast<qe::MessageType>(EntityMessage::NextLevel));
		m_systemManager->getMessageDispatch()->dispatch(msg);
	}
}

void S_Consumption::handleEvent(const qe::EntityId& entityId, const qe::EntityEventType & event) {
	auto entities = m_systemManager->getEntityManager();

	switch (static_cast<EntityEvent>(event)) {
		case EntityEvent::Remove:
			entities->removeEntity(entityId);
			break;
	}
}