#pragma once
#include "S_Base.h"
#include "C_State.h"

class S_State : public S_Base {
public:
	S_State(SystemManager* systemManager);
	~S_State();

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);

private:
	void ChangeState(const EntityId& entity, const EntityState& entityState, bool force);
};