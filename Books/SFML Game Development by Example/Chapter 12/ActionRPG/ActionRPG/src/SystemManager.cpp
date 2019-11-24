#include "SystemManager.h"

#include "EntityManager.h"

SystemManager::SystemManager() : m_entityManager(nullptr) {
	m_systems[System::State] = new S_State(this);
	m_systems[System::Control] = new S_Control(this);
	m_systems[System::Movement] = new S_Movement(this);
	m_systems[System::Collision] = new S_Collision(this);
	m_systems[System::SheetAnimation] = new S_SheetAnimation(this);
	//m_systems[System::Sound] = new S_Sound(this);
	m_systems[System::Renderer] = new S_Renderer(this);
}

SystemManager::~SystemManager() {
	PurgeSystems();
}

void SystemManager::SetEntityManager(EntityManager* entityManager) {
	if (!m_entityManager) {
		m_entityManager = entityManager;
	}
}

EntityManager* SystemManager::GetEntityManager() {
	return m_entityManager;
}

MessageHandler* SystemManager::GetMessageHandler() {
	return &m_messages;
}

void SystemManager::AddEvent(const EntityId& entity, const EventId& event) {
	m_events[entity].AddEvent(event);
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

void SystemManager::Draw(Window * window, unsigned int elevation) {
	auto iter = m_systems.find(System::Renderer);
	if (iter == m_systems.end()) return;

	// Note: Renderer System is a special case that performs drawing operations...
	S_Renderer* system = dynamic_cast<S_Renderer*>(iter->second);
	system->Render(window, elevation);
}

void SystemManager::EntityModified(const EntityId & entity, const Bitmask & bits) {
	for (auto& sIter : m_systems) {
		S_Base* system = sIter.second;

		if (system->FitsRequirements(bits)) {
			if (!system->HasEntity(entity)) {
				system->AddEntity(entity);
			}
		}
		else {
			if (system->HasEntity(entity)) {
				system->RemoveEntity(entity);
			}
		}
	}
}

void SystemManager::RemoveEntity(const EntityId & entity) {
	for (auto& system : m_systems) {
		system.second->RemoveEntity(entity);
	}
}

void SystemManager::PurgeEntities() {
	for (auto& system : m_systems) {
		system.second->Purge();
	}
}

void SystemManager::PurgeSystems() {
	for (auto& system : m_systems) {
		system.second->Purge();
	}
}

void SystemManager::SetDebugOverlay(DebugOverlay* debugOverlay) {
	m_debugOverlay = debugOverlay;
}