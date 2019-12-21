#pragma once

#include "qe/ECS/S_Base.h"

class S_Control : public qe::S_Base {
public:
	S_Control(qe::SystemManager* systemManager);
	~S_Control();

	// Inherited via S_Base
	virtual void notify(const qe::Message & message) override;
	virtual void update(float dt) override;
	virtual void handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) override;
};