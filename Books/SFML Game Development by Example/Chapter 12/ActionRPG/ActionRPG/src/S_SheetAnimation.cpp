#include "S_SheetAnimation.h"

#include "SystemManager.h"

S_SheetAnimation::S_SheetAnimation(SystemManager* systemManager) :
	S_Base(System::SheetAnimation, systemManager) {

	Bitmask req;
	req.TurnOnBit(static_cast<unsigned int>(Component::SpriteSheet));
	req.TurnOnBit(static_cast<unsigned int>(Component::State));
	m_requiredComponents.push_back(req);

	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::State_Changed, this);
}

S_SheetAnimation::~S_SheetAnimation() = default;

void S_SheetAnimation::Update(float dt) {
	EntityManager* entities = m_systemManager->GetEntityManager();

	for (auto& entity : m_entities) {
		C_SpriteSheet* sheet = entities->GetComponent<C_SpriteSheet>(entity, Component::SpriteSheet);
		C_State* state = entities->GetComponent<C_State>(entity, Component::State);

		sheet->GetSpriteSheet()->Update(dt);

		const std::string& animName = sheet->GetSpriteSheet()->GetCurrentAnim()->GetName();

		if (animName == "Attack") {
			if (!sheet->GetSpriteSheet()->GetCurrentAnim()->IsPlaying()) {
				Message msg(static_cast<MessageType>(EntityMessage::Switch_State));
				msg.m_receiver = entity;
				msg.m_int = static_cast<int>(EntityState::Idle);
				
				m_systemManager->GetMessageHandler()->Dispatch(msg);
			}
			else if (sheet->GetSpriteSheet()->GetCurrentAnim()->IsInAction()) {
				Message msg(static_cast<MessageType>(EntityMessage::Attack_Action));
				msg.m_sender = entity;
				m_systemManager->GetMessageHandler()->Dispatch(msg);
			}
		}
		else if (animName == "Death" && !sheet->GetSpriteSheet()->GetCurrentAnim()->IsPlaying()) {
			Message msg(static_cast<MessageType>(EntityMessage::Dead));
			msg.m_receiver = entity;
			m_systemManager->GetMessageHandler()->Dispatch(msg);
		}

		if (sheet->GetSpriteSheet()->GetCurrentAnim()->CheckMoved()) {
			int frame = sheet->GetSpriteSheet()->GetCurrentAnim()->GetFrame();

			Message msg(static_cast<MessageType>(EntityMessage::Frame_Change));
			msg.m_receiver = entity;
			msg.m_int = frame;

			m_systemManager->GetMessageHandler()->Dispatch(msg);
		}
	}
}

void S_SheetAnimation::HandleEvent(const EntityId & entity, const EntityEvent & event) {}

void S_SheetAnimation::Notify(const Message & message) {
	if (!HasEntity(message.m_receiver)) return;

	EntityMessage m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::State_Changed: {
			EntityState s = static_cast<EntityState>(message.m_int);

			switch (s) {
				case EntityState::Idle:
					ChangeAnimation(message.m_receiver, "Idle", true, true);
					break;

				case EntityState::Walking:
					ChangeAnimation(message.m_receiver, "Walk", true, true);
					break;

				case EntityState::Attacking:
					ChangeAnimation(message.m_receiver, "Attack", true, false);
					break;

				case EntityState::Hurt:
					break;

				case EntityState::Dying:
					ChangeAnimation(message.m_receiver, "Death", true, false);
					break;
			}

			break;
		}
	}
}

void S_SheetAnimation::ChangeAnimation(const EntityId & entity, const std::string & anim, bool play, bool loop) {
	C_SpriteSheet* sheet = m_systemManager->GetEntityManager()->GetComponent<C_SpriteSheet>(entity, Component::SpriteSheet);
	sheet->GetSpriteSheet()->SetAnimation(anim, play, loop);
}