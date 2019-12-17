#include "ECS/PacMan_EntityManager.h"

PacMan_EntityManager::PacMan_EntityManager(PacMan_SystemManager * systemManager) :
	qe::EntityManager(systemManager) {
}

int PacMan_EntityManager::addEntity(const qe::Bitmask & mask) {
	return qe::EntityManager::addEntity(mask);
}