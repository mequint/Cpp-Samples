#include "ECS/Systems/Sys_State.h"

#include "qe/ECS/Core/SystemManager.h"

#include "ECS/Components/Comp_State.h"
#include "Utilities/Directions.h"

Sys_State::Sys_State(qe::SystemManager * systemManager) :
	Sys_Base(System::State, systemManager) {

	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::State));
	m_requiredComponents.push_back(req);

	m_systemManager->GetMessageDispatcher()->Subscribe(EntityMessage::Move, this);
	m_systemManager->GetMessageDispatcher()->Subscribe(EntityMessage::Stop_Moving, this);
}

Sys_State::~Sys_State() = default;

void Sys_State::Update(float dt) {
}

void Sys_State::HandleEvent(const qe::EntityId & entity, const qe::EntityEvent & event) {
}

void Sys_State::Notify(const qe::Message & message) {
	EntityMessage m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::Move: {
			qe::EntityEvent e;
			Direction dir = static_cast<Direction>(message.m_int);

			if (dir == Direction::Up) {
				e = qe::EntityEvent::Moving_Up;
			}
			else if (dir == Direction::Down) {
				e = qe::EntityEvent::Moving_Down;
			}

			m_systemManager->AddEvent(message.m_receiver, static_cast<qe::EventId>(e));
			
			break;
		}

		case EntityMessage::Stop_Moving: {
			m_systemManager->AddEvent(message.m_receiver, static_cast<qe::EventId>(qe::EntityEvent::Stop));
		}
	}
}