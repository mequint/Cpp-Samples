#pragma once

#include <unordered_map>

#include "DebugOverlay.h"
#include "MessageHandler.h"
#include "S_Collision.h"
#include "S_Control.h"
#include "S_Movement.h"
#include "S_Renderer.h"
#include "S_SheetAnimation.h"
#include "S_Sound.h"
#include "S_State.h"
#include "Window.h"

using SystemContainer = std::unordered_map<System, S_Base*>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;

class EntityManager;

class SystemManager {
public:
	SystemManager();
	~SystemManager();

	void SetEntityManager(EntityManager* entityManager);
	EntityManager* GetEntityManager();
	MessageHandler* GetMessageHandler();

	template <class T>
	T* GetSystem(const System& system) {
		auto iter = m_systems.find(system);

		return (iter != m_systems.end() ? dynamic_cast<T*>(iter->second) : nullptr);
	}

	void AddEvent(const EntityId& entity, const EventId& event);
	
	void Update(float dt);
	void HandleEvents();
	void Draw(Window* window, unsigned int elevation);

	void EntityModified(const EntityId& entity, const Bitmask& bits);
	void RemoveEntity(const EntityId& entity);

	void PurgeEntities();
	void PurgeSystems();

	void SetDebugOverlay(DebugOverlay* debugOverlay);

private:
	SystemContainer m_systems;
	EntityManager* m_entityManager;
	EntityEventContainer m_events;

	MessageHandler m_messages;

	DebugOverlay* m_debugOverlay;
};