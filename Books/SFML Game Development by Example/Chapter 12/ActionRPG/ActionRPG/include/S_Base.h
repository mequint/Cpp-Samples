#pragma once

#include "EventQueue.h"
#include "EntityEvents.h"
#include "EntityManager.h"
#include "Observer.h"

using EntityList = std::vector<EntityId>;
using Requirements = std::vector<Bitmask>;

class SystemManager;

class S_Base : public Observer {
public:
	S_Base(const System& id, SystemManager* systemManager);
	virtual ~S_Base();

	bool AddEntity(const EntityId& entity);
	bool HasEntity(const EntityId& entity);
	bool RemoveEntity(const EntityId& entity);

	System GetId();

	bool FitsRequirements(const Bitmask& bits);
	void Purge();

	virtual void Update(float dt) = 0;
	virtual void HandleEvent(const EntityId& entity, const EntityEvent& event) = 0;

protected:
	System m_id;
	Requirements m_requiredComponents;
	EntityList m_entities;

	SystemManager* m_systemManager;
};