#include "qe/ECS/SystemManager.h"

qe::SystemManager::SystemManager() :
	m_entityManager(nullptr) {
}

qe::SystemManager::~SystemManager() {
	cleanupSystems();
}

void qe::SystemManager::setEntityManager(EntityManager * entityManager) {
	if (!m_entityManager) {
		m_entityManager = entityManager;
	}
}

qe::EntityManager* qe::SystemManager::getEntityManager() {
	return m_entityManager;
}

qe::MessageDispatch * qe::SystemManager::getMessageDispatch() {
	return &m_messages;
}

void qe::SystemManager::addEvent(const EntityId & entityId, const EntityEventType & eventId) {
	m_events[entityId].addEvent(eventId);
}

void qe::SystemManager::update(float dt) {
	for (auto& iter : m_systems) {
		iter.second->update(dt);
	}

	handleEvents();
}

void qe::SystemManager::handleEvents() {
	for (auto& event : m_events) {
		EntityEventType id = 0;

		while (event.second.processEvents(id)) {
			for (auto& system : m_systems) {
				if (system.second->hasEntity(event.first)) {
					system.second->handleEvent(event.first, static_cast<EntityEventType>(id));
				}
			}
		}
	}
}

void qe::SystemManager::updateEntity(const EntityId & entityId, const Bitmask & bits) {
	for (auto& iter : m_systems) {
		auto& system = iter.second;

		if (system->meetsRequirements(bits)) {
			if (!system->hasEntity(entityId)) {
				system->addEntity(entityId);
			}
		}
		else {
			if (system->hasEntity(entityId)) {
				system->removeEntity(entityId);
			}
		}
	}
}

void qe::SystemManager::removeEntity(const EntityId & entityId) {
	for (auto& system : m_systems) {
		system.second->removeEntity(entityId);
	}
}

void qe::SystemManager::cleanupEntities() {
	if (m_systems.size() == 0) return;

	for (auto& system : m_systems) {
		system.second->cleanup();
	}
}

void qe::SystemManager::cleanupSystems() {
	if (m_systems.size() == 0) return;

	m_systems.clear();
}