#include "qe/ECS/EntityManager.h"

#include <algorithm>

#include "qe/ECS/SystemManager.h"

qe::EntityManager::EntityManager(SystemManager * systemManager) : 
	m_idCounter(0), 
	m_systemManager(systemManager) {}

qe::EntityManager::~EntityManager() {
	cleanup();
}

int qe::EntityManager::addEntity(const Bitmask& mask) {
	unsigned int entityId = m_idCounter;
	if (!m_entities.emplace(entityId, EntityData(0, ComponentContainer())).second) {
		return -1;
	}

	++m_idCounter;
	for (int i = 0; i < static_cast<int>(mask.size()); ++i) {
		if (mask[i]) {
			addComponent(entityId, i);
		}
	}

	m_systemManager->updateEntity(entityId, mask);
	//m_systemManager->addEvent(entityId, static_cast<EventId>(EntityEvent::Spawned));		// TODO: Ties entity to available events...extend...

	return entityId;
}

bool qe::EntityManager::removeEntity(const EntityId & entityId) {
	auto iter = m_entities.find(entityId);
	if (iter == m_entities.end()) return false;

	m_entities.erase(iter);
	m_systemManager->removeEntity(entityId);

	if (m_entities.size() == 0) m_idCounter = 0;

	return true;
}

bool qe::EntityManager::addComponent(const EntityId & entityId, const ComponentType & component) {
	auto iter = m_entities.find(entityId);
	if (iter == m_entities.end()) return false;

	if (iter->second.first[component]) return false;

	auto iter2 = m_componentFactory.find(component);
	if (iter2 == m_componentFactory.end()) return false;

	iter->second.second.emplace_back(ComponentPtr(iter2->second()));
	iter->second.first.set(component);

	m_systemManager->updateEntity(entityId, iter->second.first);

	return true;
}

bool qe::EntityManager::removeComponent(const EntityId & entityId, const ComponentType & component) {
	auto iter = m_entities.find(entityId);
	if (iter == m_entities.end()) return false;

	if (iter->second.first[component]) return false;

	auto& container = iter->second.second;
	auto compIter = std::find_if(container.begin(), container.end(), [component](ComponentPtr& c) {
		return c->getType() == component;
	});

	if (compIter == container.end()) return false;

	container.erase(compIter);
	iter->second.first.set(component, false);

	m_systemManager->updateEntity(entityId, iter->second.first);

	return true;
}

bool qe::EntityManager::hasComponent(const EntityId & entityId, const ComponentType & component) {
	auto iter = m_entities.find(entityId);
	if (iter == m_entities.end()) return false;

	return iter->second.first[component];
}

void qe::EntityManager::cleanup() {
	m_systemManager->cleanupEntities();
	m_entities.clear();
	m_idCounter = 0;
}