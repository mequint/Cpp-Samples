#pragma once

#include "S_Base.h"

class S_Control : public S_Base {
public:
	S_Control(SystemManager* systemManager);
	~S_Control();

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);

private:
	void MoveEntity(const EntityId& entity, const Direction& dir);
};