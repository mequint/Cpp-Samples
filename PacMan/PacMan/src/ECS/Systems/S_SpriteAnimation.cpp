#include "ECS/Systems/S_SpriteAnimation.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_AnimatedSprite.h"
#include "ECS/Components/C_State.h"
#include "qe/ECS/SystemManager.h"
#include "Utilities/eDirections.h"

S_SpriteAnimation::S_SpriteAnimation(qe::SystemManager * systemManager) : 
	qe::S_Base(static_cast<qe::SystemType>(System::SpriteAnimation), systemManager) {

	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::State));
	bits.set(static_cast<qe::ComponentType>(Component::AnimatedSprite));
	m_requiredComponents.push_back(bits);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::RequestMove), this);	
	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::Stop), this);
}

S_SpriteAnimation::~S_SpriteAnimation() = default;

void S_SpriteAnimation::notify(const qe::Message & message) {
	if (!hasEntity(message.m_receiver)) return;

	auto messageType = static_cast<EntityMessage>(message.m_type);

	auto direction = static_cast<eDirection>(message.m_int);

	switch (messageType) {
		case EntityMessage::Stop:
			switch (direction) {
				case eDirection::Up: {
					changeAnimation(message.m_receiver, "StopUp", true);
					break;
				}

				case eDirection::Down: {
					changeAnimation(message.m_receiver, "StopDown", true);
					break;
				}

				case eDirection::Left: {
					changeAnimation(message.m_receiver, "StopLeft", true);
					break;
				}

				case eDirection::Right: {
					changeAnimation(message.m_receiver, "StopRight", true);
					break;
				}
			}
			break;

		case EntityMessage::RequestMove:
			switch (direction) {
				case eDirection::Up: {
					changeAnimation(message.m_receiver, "MoveUp", true);
					break;
				}

				case eDirection::Down: {
					changeAnimation(message.m_receiver, "MoveDown", true);
					break;
				}

				case eDirection::Left: {
					changeAnimation(message.m_receiver, "MoveLeft", true);
					break;
				}

				case eDirection::Right: {
					changeAnimation(message.m_receiver, "MoveRight", true);
					break;
				}
			}
			break;
	}
}

void S_SpriteAnimation::update(float dt) {
	auto entityManager = m_systemManager->getEntityManager();

	for (auto& entity : m_entities) {
		auto animatedSprite = entityManager->getComponent<C_AnimatedSprite>(entity, static_cast<qe::ComponentType>(Component::AnimatedSprite));
		auto state = entityManager->getComponent<C_State>(entity, static_cast<qe::ComponentType>(Component::State));

		animatedSprite->getSprite()->update(dt);
	}
}

void S_SpriteAnimation::handleEvent(const qe::EntityId & entity, const qe::EntityEventType & event) {}

void S_SpriteAnimation::changeAnimation(const qe::EntityId & entity, const std::string& action, bool play) {
	auto animation = m_systemManager->getEntityManager()->getComponent<C_AnimatedSprite>(entity, static_cast<qe::ComponentType>(Component::AnimatedSprite));
	animation->getSprite()->changeAnimation(action, play);
}