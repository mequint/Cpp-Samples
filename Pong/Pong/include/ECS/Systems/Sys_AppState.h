#pragma once

#include "qe/ECS/Core/Sys_Base.h"
#include "qe/State/StateManager.h"

// The App State system wraps the application state manager into the ECS to enable the game to send signals back to the
//	application.  Example:  The Game Over state needs to be loaded when the player "dies" or the Game state needs to load
//	the next level and be reset.

// This will primarily be implemented through the Notify method

class Sys_AppState : public qe::Sys_Base {
public:
	Sys_AppState(qe::SystemManager* systemManager);
	~Sys_AppState();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& id, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);

	void SetStateManager(qe::StateManager* stateManager);

private:
	qe::StateManager* m_stateManager;
};