#pragma once

#include "qe/ECS/S_Base.h"
#include "qe/Utilities/RandomGenerator.h"

#include "Tile/TileMapManager.h"

class S_AI : public qe::S_Base {
public:
	S_AI(qe::SystemManager* systemManager);
	~S_AI();

	virtual void notify(const qe::Message& message) override;
	virtual void update(float dt) override;
	virtual void handleEvent(const qe::EntityId& entityId, const qe::EntityEventType& event) override;

	void setRandomGenerator(qe::RandomGenerator* random);
	void setMapManager(TileMapManager* mapManager);

private:
	qe::RandomGenerator* m_random;
	TileMapManager* m_mapManager;
};