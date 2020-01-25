#pragma once

#include "qe/ECS/S_Base.h"
#include "qe/State/StateManager.h"

// Wrapper for the Application State Manager
class S_AppState : public qe::S_Base {
public:
	S_AppState(qe::SystemManager* systemManager);

	virtual void notify(const qe::Message & message) override;
	virtual void update(float dt) override;
	virtual void handleEvent(const qe::EntityId& entityId, const qe::EntityEventType& event) override;

	void setStateManager(qe::StateManager* stateManager);

private:
	qe::StateManager* m_stateManager;
};