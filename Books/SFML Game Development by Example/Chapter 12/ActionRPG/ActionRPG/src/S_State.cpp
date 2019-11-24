#include "S_State.h"

#include "SystemManager.h"

S_State::S_State(SystemManager * systemManager) : 
	S_Base(System::State, systemManager) {
	Bitmask req;
	req.TurnOnBit(static_cast<unsigned int>(Component::State));
	m_requiredComponents.push_back(req);

	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Move, this);
	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Switch_State, this);
}

S_State::~S_State() = default;

void S_State::Update(float dt) {
	EntityManager* entities = m_systemManager->GetEntityManager();

	for (auto& entity : m_entities) {
		C_State* state = entities->GetComponent<C_State>(entity, Component::State);

		if (state->GetState() == EntityState::Walking) {
			Message msg(static_cast<MessageType>(EntityMessage::Is_Moving));
			msg.m_receiver = entity;
			m_systemManager->GetMessageHandler()->Dispatch(msg);
		}
	}
}

void S_State::HandleEvent(const EntityId & entity, const EntityEvent & event) {
	switch (event) {
		case EntityEvent::Became_Idle:
			ChangeState(entity, EntityState::Idle, false);
			break;
	}
}

void S_State::Notify(const Message & message) {
	if (!HasEntity(message.m_receiver)) return;

	EntityMessage m = static_cast<EntityMessage>(message.m_type);
	
	switch (m) {
		case EntityMessage::Move: {
			C_State* state = m_systemManager->GetEntityManager()->GetComponent<C_State>(message.m_receiver, Component::State);

			if (state->GetState() == EntityState::Dying) return;

			Direction dir = static_cast<Direction>(message.m_int);

			EntityEvent e;

			switch (dir) {
				case Direction::Up: e = EntityEvent::Moving_Up; break;
				case Direction::Down: e = EntityEvent::Moving_Down; break;
				case Direction::Left: e = EntityEvent::Moving_Left; break;
				case Direction::Right: e = EntityEvent::Moving_Right; break;
			}

			m_systemManager->AddEvent(message.m_receiver, static_cast<EventId>(e));
			ChangeState(message.m_receiver, EntityState::Walking, false);

			break;
		}

		case EntityMessage::Switch_State: {
			ChangeState(message.m_receiver, static_cast<EntityState>(message.m_int), false);
			break;
		}
	}
}

void S_State::ChangeState(const EntityId & entity, const EntityState & entityState, bool force) {
	EntityManager* entities = m_systemManager->GetEntityManager();

	C_State* state = entities->GetComponent<C_State>(entity, Component::State);
	if (!force && state->GetState() == EntityState::Dying) return;

	state->SetState(entityState);

	Message msg(static_cast<MessageType>(EntityMessage::State_Changed));
	msg.m_receiver = entity;
	msg.m_int = static_cast<int>(entityState);

	m_systemManager->GetMessageHandler()->Dispatch(msg);
}