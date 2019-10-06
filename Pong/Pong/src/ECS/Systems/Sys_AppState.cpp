#include "qe/ECS/Core/SystemManager.h"

#include "ECS/Systems/Sys_AppState.h"
#include "Utilities/Directions.h"

Sys_AppState::Sys_AppState(qe::SystemManager* systemManager) :
	Sys_Base(System::AppState, systemManager),
	m_stateManager(nullptr) {
	m_systemManager->GetMessageDispatcher()->Subscribe(EntityMessage::Health_Depleted, this);
}

Sys_AppState::~Sys_AppState() = default;

void Sys_AppState::Update(float dt) {}

void Sys_AppState::HandleEvent(const qe::EntityId & id, const qe::EntityEvent & event) {}

void Sys_AppState::Notify(const qe::Message& message) {
	if (!m_stateManager) {
		// Error...either I forgot to set the state manager or something happened to delete the original state manager
		// The game will just keep playing in its weird state
		return;
	}

	EntityMessage m = static_cast<EntityMessage>(message.m_type);
	switch (m) {
		case EntityMessage::Health_Depleted: {
			Direction dir = static_cast<Direction>(message.m_int);

			if (dir == Direction::Left) {
				// Set the intermediate data to winner being player 1...
				m_stateManager->ChangeState(qe::StateType::GameOver); 
			}
			else {
				// Set the intermediate data to winnner being player 2...
				m_stateManager->ChangeState(qe::StateType::GameOver);
			}
		}
	}
}

void Sys_AppState::SetStateManager(qe::StateManager* stateManager) {
	m_stateManager = stateManager;
}