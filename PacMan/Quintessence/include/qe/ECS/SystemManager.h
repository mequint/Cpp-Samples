#pragma once

#include <memory>
#include <unordered_map>

#include "qe/ECS/EntityEventQueue.h"
#include "qe/Messaging/MessageDispatch.h"
#include "qe/ECS/S_Base.h"

namespace qe {
	class EntityManager;
	class Window;

	using SystemContainer = std::unordered_map<SystemType, std::unique_ptr<S_Base>>;
	using EntityEventContainer = std::unordered_map<EntityId, EntityEventQueue>;

	class SystemManager {
	public:
		SystemManager();
		virtual ~SystemManager();

		void setEntityManager(EntityManager* entityManager);
		EntityManager* getEntityManager();
		MessageDispatch* getMessageDispatch();

		template <class T>
		void registerSystem(const SystemType& system) {
			m_systems[system] = std::make_unique<T>(this);
		}

		template <class T>
		T* getSystem(const SystemType& system) {
			auto iter = m_systems.find(system);
			return (iter != m_systems.end()) ? dynamic_cast<T*>(iter->second.get()) : nullptr;
		}

		void addEvent(const EntityId& entityId, const EntityEventType& eventId);

		void update(float dt);
		void handleEvents();
		virtual void draw(qe::Window* window) = 0;

		void updateEntity(const EntityId& entityId, const Bitmask& bits);
		void removeEntity(const EntityId& entityId);

		void cleanupEntities();
		void cleanupSystems();

	protected:
		SystemContainer m_systems;

		EntityManager* m_entityManager;
		EntityEventContainer m_events;
		MessageDispatch m_messages;
	};
}