#pragma once

#include "qe/ECS/S_Base.h"
#include "qe/Window/Window.h"
#include "Tile/TileMapManager.h"

struct Collision {
	Collision(float area, Tile* tile, sf::FloatRect& bounds) :
		Area(area), Tile(tile), Bounds(bounds) {}

	float Area;
	Tile* Tile;
	sf::FloatRect Bounds;
};

using Collisions = std::vector<Collision>;

class S_Collision : public qe::S_Base {
public:
	S_Collision(qe::SystemManager* systemManager);
	~S_Collision();

	// Inherited via S_Base
	virtual void notify(const qe::Message & message) override;
	virtual void update(float dt) override;
	virtual void handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) override;

	void setTileMapManager(TileMapManager* mapManager);

	void render(qe::Window* window);

private:
	TileMapManager* m_mapManager;
};