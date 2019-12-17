#pragma once

#include "qe\ECS\EntityManager.h"

#include "ECS\PacMan_SystemManager.h"

class PacMan_EntityManager : public qe::EntityManager {
public:
	PacMan_EntityManager(PacMan_SystemManager* systemManager);

	virtual int addEntity(const qe::Bitmask& mask);
};