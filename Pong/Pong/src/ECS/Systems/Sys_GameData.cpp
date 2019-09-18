#include "ECS/Systems/Sys_GameData.h"

#include "ECS/Components/Comp_Text.h"
#include "Utilities/Directions.h"
#include <qe/ECS/Core/SystemManager.h>

Sys_GameData::Sys_GameData(qe::SystemManager * systemManager) :Sys_Base(System::GameData, systemManager) {
	m_leftPoints = 0;
	m_rightPoints = 0;

	m_systemManager->GetMessageDispatcher()->Subscribe(EntityMessage::Out_Of_Bounds, this);
}

void Sys_GameData::Update(float dt) {
}

void Sys_GameData::HandleEvent(const qe::EntityId& entityId, const qe::EntityEvent& event) {
}

void Sys_GameData::Notify(const qe::Message& message) {
	EntityMessage m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::Out_Of_Bounds: {
			Direction dir = static_cast<Direction>(message.m_int);

			auto entities = m_systemManager->GetEntityManager();

			if (dir == Direction::Left) {
				m_leftPoints += 1;

				auto scoreboard = entities->GetComponent<Comp_Text>(m_leftEntity, Component::Text);
				scoreboard->SetText(std::to_string(m_leftPoints));
			}
			else if (dir == Direction::Right) {
				m_rightPoints += 1;

				auto scoreboard = entities->GetComponent<Comp_Text>(m_rightEntity, Component::Text);
				scoreboard->SetText(std::to_string(m_rightPoints));
			}

			break;
		}
	}
}

void Sys_GameData::SetLeftEntity(int id) {
	m_leftEntity = id;
}

void Sys_GameData::SetRightEntity(int id) {
	m_rightEntity = id;
}

void Sys_GameData::Reset() {
	m_leftPoints = 0;
	m_rightPoints = 0;
}