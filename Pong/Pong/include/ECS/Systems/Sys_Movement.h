#pragma once

#include "qe\ECS\Core\Sys_Base.h"

class Sys_Movement : public qe::Sys_Base {
public:
	Sys_Movement(qe::SystemManager* systemManager);
	~Sys_Movement();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entity, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);
};