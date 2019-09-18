#pragma once

#include <vector>

#include "qe/ECS/ECS_Types.h"
#include "qe/ECS/EntityEvents.h"
#include "qe/ECS/Core/EntityManager.h"
#include "qe/Messaging/Observer.h"

namespace qe {
	// Forward declaration
	class SystemManager;

	using EntityList = std::vector<EntityId>;
	using Requirements = std::vector<Bitmask>;

	class Sys_Base : public Observer {
	public:
		Sys_Base(const System& id, SystemManager* systemManager);
		virtual ~Sys_Base();

		bool AddEntity(const EntityId& entityId);
		bool HasEntity(const EntityId& entityId);
		bool RemoveEntity(const EntityId& entityId);

		System GetId() const;

		bool MeetsRequirements(const Bitmask& bits)  const;
		void Cleanup();

		virtual void Update(float dt) = 0;
		virtual void HandleEvent(const EntityId& entityId, const EntityEvent& event) = 0;

	protected:
		System m_id;
		Requirements m_requiredComponents;
		EntityList m_entities;

		SystemManager* m_systemManager;
	};
}