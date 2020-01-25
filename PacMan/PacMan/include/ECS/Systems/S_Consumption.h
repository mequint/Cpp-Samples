#pragma once

#include "qe/ECS/S_Base.h"

class S_Consumption : public qe::S_Base {
public:
	S_Consumption(qe::SystemManager* systemManager);

	// Inherited via S_Base
	virtual void notify(const qe::Message& message) override;
	virtual void update(float dt) override;
	virtual void handleEvent(const qe::EntityId& entityId, const qe::EntityEventType& event) override;
private:


};