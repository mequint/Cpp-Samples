#pragma once

#include "qe/ECS/S_Base.h"

#include "Utilities/Directions.h"
#include "Tile/TileMapManager.h"

class S_Movement : public qe::S_Base {
public:
	S_Movement(qe::SystemManager* systemManager);
	~S_Movement();

	// Inherited via S_Base
	virtual void notify(const qe::Message & message) override;

	virtual void update(float dt) override;

	virtual void handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) override;

	void setMapManager(TileMapManager* mapManager);

private:
	Direction _getPhysicalDirection(const sf::Vector2f& velocity);

	TileMapManager* m_mapManager;

	float m_timeStep;
	float m_currentTime;
};