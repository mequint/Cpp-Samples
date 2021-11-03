#pragma once

#include "ECS/Components/C_State.h"
#include "qe/ECS/S_Base.h"
#include "Tile/TileMapManager.h"

class S_State : public qe::S_Base {
public:
	S_State(qe::SystemManager* systemManager);
	~S_State();


	// Inherited via S_Base
	virtual void notify(const qe::Message & message) override;

	virtual void update(float dt) override;

	virtual void handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) override;

private:
	void _changeState(const qe::EntityId& entityId, const eEntityState& entityState);
};