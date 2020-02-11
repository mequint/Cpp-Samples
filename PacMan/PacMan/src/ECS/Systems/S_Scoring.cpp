#include "ECS/Systems/S_Scoring.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Points.h"
#include "ECS/Components/C_Score.h"
#include "qe/ECS/SystemManager.h"

S_Scoring::S_Scoring(qe::SystemManager* systemManager) : 
	qe::S_Base(static_cast<qe::SystemType>(System::Scoring), systemManager) {
	
	qe::Bitmask bits;
	bits.set(static_cast<qe::ComponentType>(Component::Score));
	m_requiredComponents.push_back(bits);

	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::UpdateScore), this);
}

void S_Scoring::notify(const qe::Message & message) {
	auto entities = m_systemManager->getEntityManager();

	switch (static_cast<EntityMessage>(message.m_type)) {
		case EntityMessage::UpdateScore: {
			for (auto entity : m_entities) {
				auto score = entities->getComponent<C_Score>(entity, static_cast<qe::ComponentType>(Component::Score));
				auto points = entities->getComponent<C_Points>(message.m_sender, static_cast<qe::ComponentType>(Component::Points));

				score->setScore(score->getScore() + points->getPoints());

				break;
			}
		}
	}
}

void S_Scoring::update(float dt) {
}

void S_Scoring::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
}