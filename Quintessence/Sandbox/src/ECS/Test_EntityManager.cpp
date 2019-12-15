#include "ECS/Test_EntityManager.h"

Test_EntityManager::Test_EntityManager(Test_SystemManager* systemManager) : qe::EntityManager(systemManager) {
}

int Test_EntityManager::addEntity(const qe::Bitmask & mask) {
	// Make sure to call the base class add entity...we make this extendable to add additional event work
	int id = qe::EntityManager::addEntity(mask);

	return id;
}