#include "ECS/Systems/S_AppState.h"

#include "ECS/ECS_Types.h"
#include "States/State_Game.h"

#include "qe/ECS/SystemManager.h"

S_AppState::S_AppState(qe::SystemManager* systemManager) :
	qe::S_Base(static_cast<qe::SystemType>(System::AppState), systemManager) {
	m_systemManager->getMessageDispatch()->subscribe(static_cast<qe::MessageType>(EntityMessage::NextLevel), this);
}

void S_AppState::notify(const qe::Message & message) {
	switch (static_cast<EntityMessage>(message.m_type)) {
		case EntityMessage::NextLevel: {
			auto currentState = m_stateManager->getCurrentState<State_Game>();

			currentState->nextLevel();
			break;
		}
	}
}

void S_AppState::update(float dt) {}

void S_AppState::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}

void S_AppState::setStateManager(qe::StateManager* stateManager) {
	m_stateManager = stateManager;
}