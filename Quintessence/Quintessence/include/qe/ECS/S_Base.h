#pragma once

#include "EntityEventType.h"
#include "EntityManager.h"
#include "qe/Messaging/Subscriber.h"

namespace qe {
	using SystemType = unsigned int;

	class SystemManager;

	using EntityList = std::vector<EntityId>;
	using SystemRequirements = std::vector<Bitmask>;

	class S_Base : public Subscriber {
	public:
		S_Base(const SystemType& id, SystemManager* systemManager);
		virtual ~S_Base();

		bool addEntity(const EntityId& entityId);
		bool hasEntity(const EntityId& entityId);
		bool removeEntity(const EntityId& entityId);

		SystemType getId() const;

		bool meetsRequirements(const Bitmask& bits) const;

		void cleanup();

		virtual void update(float dt) = 0;
		virtual void handleEvent(const EntityId& entityId, const EntityEventType& event) = 0;

	protected:
		SystemType m_id;
		SystemRequirements m_requiredComponents;
		EntityList m_entities;

		SystemManager* m_systemManager;
	};
}