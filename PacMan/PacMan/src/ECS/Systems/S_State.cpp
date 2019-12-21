#include "ECS/Systems/S_State.h"

#include "ECS/ECS_Types.h"
#include "Utilities/Directions.h"

#include "qe/ECS/SystemManager.h"

S_State::S_State(qe::SystemManager * systemManager) : 
	S_Base(static_cast<qe::SystemType>(System::State), systemManager) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::State));
	m_requiredComponents.push_back(req);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::Move), this);
	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::Stop), this);
}

S_State::~S_State() = default;

void S_State::notify(const qe::Message & message) {
	EntityMessage m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::Move: {
			Direction dir = static_cast<Direction>(message.m_int);
			qe::EntityEventType e;

			if (dir == Direction::Up) {
				e = static_cast<qe::EntityEventType>(EntityEvent::Moving_Up);
			}
			else if (dir == Direction::Down) {
				e = static_cast<qe::EntityEventType>(EntityEvent::Moving_Down);
			}
			else if (dir == Direction::Left) {
				e = static_cast<qe::EntityEventType>(EntityEvent::Moving_Left);
			}
			else if (dir == Direction::Right) {
				e = static_cast<qe::EntityEventType>(EntityEvent::Moving_Right);
			}

			m_systemManager->addEvent(message.m_receiver, e);
			break;
		}

		case EntityMessage::Stop: {
			m_systemManager->addEvent(message.m_receiver, static_cast<qe::EntityEventType>(EntityEvent::Stop));
			break;
		}
	}
}

void S_State::update(float dt) {}

void S_State::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}