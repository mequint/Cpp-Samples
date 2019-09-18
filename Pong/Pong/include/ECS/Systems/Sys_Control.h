#pragma once

#include "Utilities/Directions.h"
#include "qe/ECS/Core/Sys_Base.h"

class Sys_Control : public qe::Sys_Base {
public:
	Sys_Control(qe::SystemManager* systemManager);
	~Sys_Control();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entityId, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);
};