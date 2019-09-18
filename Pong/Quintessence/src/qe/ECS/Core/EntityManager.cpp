#include "qe\ECS\Core\EntityManager.h"

#include <algorithm>

#include "qe\ECS\EntityEvents.h"
#include "qe\ECS\Core\SystemManager.h"

namespace qe {
	EntityManager::EntityManager(SystemManager* systemManager) : m_idCounter(0), m_systemManager(systemManager) {
	}

	EntityManager::~EntityManager() {
		Cleanup();
	}

	int EntityManager::AddEntity(const Bitmask& mask) {
		unsigned int entityId = m_idCounter;
		if (!m_entities.emplace(entityId, EntityData(0, ComponentContainer())).second) {
			return -1;
		}

		++m_idCounter;
		for (size_t i = 0; i < mask.size(); ++i) {
			if (mask[i]) {
				AddComponent(entityId, static_cast<Component>(i));
			}
		}

		m_systemManager->EntityModified(entityId, mask);
		m_systemManager->AddEvent(entityId, (EventId)EntityEvent::Spawned);

		return entityId;
	}

	bool EntityManager::RemoveEntity(const EntityId& id) {
		auto iter = m_entities.find(id);
		if (iter == m_entities.end()) return false;

		m_entities.erase(iter);
		m_systemManager->RemoveEntity(id);

		if (static_cast<int>(m_entities.size()) == 0) m_idCounter = 0;

		return true;
	}

	bool EntityManager::AddComponent(const EntityId& entityId, const Component& component) {
		auto iter = m_entities.find(entityId);
		if (iter == m_entities.end()) return false;

		if (iter->second.first[static_cast<size_t>(component)]) return false;

		auto iter2 = m_componentFactory.find(component);
		if (iter2 == m_componentFactory.end()) return false;

		iter->second.second.emplace_back(ComponentPtr(iter2->second()));
		iter->second.first.set(static_cast<size_t>(component));

		m_systemManager->EntityModified(entityId, iter->second.first);

		return true;
	}

	bool EntityManager::RemoveComponent(const EntityId& entityId, const Component& component) {
		auto iter = m_entities.find(entityId);
		if (iter == m_entities.end()) return false;

		if (!iter->second.first[static_cast<size_t>(component)]) return false;

		auto& container = iter->second.second;
		auto compIter = std::find_if(container.begin(), container.end(), [component](ComponentPtr& c)
		{
			return c->GetType() == component;
		});

		if (compIter == container.end()) return false;
		container.erase(compIter);
		iter->second.first.set(static_cast<size_t>(component), false);

		m_systemManager->EntityModified(entityId, iter->second.first);

		return true;
	}

	bool EntityManager::HasComponent(const EntityId& entityId, const Component & component) {
		auto iter = m_entities.find(entityId);
		if (iter == m_entities.end()) return false;

		return iter->second.first[static_cast<size_t>(component)];
	}

	void EntityManager::Cleanup() {
		m_systemManager->CleanupEntities();
		m_entities.clear();
		m_idCounter = 0;
	}

	int EntityManager::GetFirstEntityId() const {
		auto iter = m_entities.begin();
		if (iter == m_entities.end()) return -1;

		return iter->first;
	}

	int EntityManager::GetLastEntityId() const {
		auto iter = m_entities.begin();
		if (iter == m_entities.end()) return -1;

		while (std::next(iter) != m_entities.end()) {
			iter++;
		}
		return iter->first;
	}
}