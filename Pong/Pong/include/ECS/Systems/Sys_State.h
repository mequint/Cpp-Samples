#pragma once

#include "qe/ECS/Core/Sys_Base.h"

class Sys_State : public qe::Sys_Base {
public:
	Sys_State(qe::SystemManager* systemManager);
	~Sys_State();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entity, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);
};