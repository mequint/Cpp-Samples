#include "qe/ECS/Core/SystemManager.h"

namespace qe {
	SystemManager::SystemManager() :
		m_entityManager(nullptr) {
	}

	SystemManager::~SystemManager() {
		CleanupSystems();
	}

	void SystemManager::SetEntityManager(EntityManager * entityManager) {
		if (!m_entityManager) {
			m_entityManager = entityManager;
		}
	}

	EntityManager* SystemManager::GetEntityManager() {
		return m_entityManager;
	}

	MessageDispatcher* SystemManager::GetMessageDispatcher() {
		return &m_messages;
	}

	void SystemManager::AddEvent(const EntityId& entityId, const EventId& eventId) {
		m_events[entityId].AddEvent(eventId);
	}

	void SystemManager::Update(float dt) {
		for (auto& iter : m_systems) {
			iter.second->Update(dt);
		}

		HandleEvents();
	}

	void SystemManager::HandleEvents() {
		for (auto& event : m_events) {
			EventId id = 0;
			while (event.second.ProcessEvents(id)) {
				for (auto& system : m_systems) {
					if (system.second->HasEntity(event.first)) {
						system.second->HandleEvent(event.first, static_cast<EntityEvent>(id));
					}
				}
			}
		}
	}

	void SystemManager::EntityModified(const EntityId & entityId, const Bitmask & bits) {
		for (auto& iter : m_systems) {
			auto& system = iter.second;

			if (system->MeetsRequirements(bits)) {
				if (!system->HasEntity(entityId)) {
					system->AddEntity(entityId);
				}
			}
			else {
				if (system->HasEntity(entityId)) {
					system->RemoveEntity(entityId);
				}
			}
		}
	}

	void SystemManager::RemoveEntity(const EntityId & entityId) {
		for (auto& system : m_systems) {
			system.second->RemoveEntity(entityId);
		}
	}

	void SystemManager::CleanupEntities() {
		for (auto& system : m_systems) {
			system.second->Cleanup();
		}
	}

	void SystemManager::CleanupSystems() {
		m_systems.clear();
	}
}