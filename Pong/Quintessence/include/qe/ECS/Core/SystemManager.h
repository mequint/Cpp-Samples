#pragma once

#include <memory>
#include <unordered_map>

#include "qe/Event/EventQueue.h"
#include "qe/Messaging/MessageDispatcher.h"
#include "qe/ECS/Core/Sys_Base.h"
#include "qe/Window/Window.h"

namespace qe {
	// Forward declaration
	class EntityManager;

	using SystemContainer = std::unordered_map<System, std::unique_ptr<Sys_Base>>;
	using EntityEventContainer = std::unordered_map <EntityId, EventQueue>;

	class SystemManager {
		public:
			SystemManager();
			~SystemManager();

			void SetEntityManager(EntityManager* entityManager);
			EntityManager* GetEntityManager();
			MessageDispatcher* GetMessageDispatcher();

			template <class T>
			void RegisterSystem(const System& system) {
				m_systems[system] = std::make_unique<T>(this);
			}

			template <class T>
			T* GetSystem(const System& system) {
				auto iter = m_systems.find(system);
				return (iter != m_systems.end()) ? dynamic_cast<T*>(iter->second.get()) : nullptr;
			}

			void AddEvent(const EntityId& entityId, const EventId& eventId);

			void Update(float dt);
			void HandleEvents();
			virtual void Draw(qe::Window* window, unsigned int layer) = 0;			// TODO: What if I don't want a Window?

			void EntityModified(const EntityId& entityId, const Bitmask& bits);
			void RemoveEntity(const EntityId& entityId);

			void CleanupEntities();
			void CleanupSystems();

		protected:
			SystemContainer m_systems;
			EntityManager* m_entityManager;
			EntityEventContainer m_events;
			MessageDispatcher m_messages;
	};
}