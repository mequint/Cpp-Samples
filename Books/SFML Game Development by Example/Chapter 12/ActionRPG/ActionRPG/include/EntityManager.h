#pragma once

#include <functional>

#include "Bitmask.h"
#include "C_Collidable.h"
#include "C_Controller.h"
#include "C_Movable.h"
#include "C_Position.h"
#include "C_SpriteSheet.h"
//#include "C_SoundEmitter.h"
//#include "C_SoundListener.h"
#include "C_State.h"
#include "TextureManager.h"

using EntityId = unsigned int;

using ComponentContainer = std::vector<C_Base*>;
using EntityData = std::pair<Bitmask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;
using ComponentFactory = std::unordered_map<Component, std::function<C_Base*(void)>>;

class SystemManager;

class EntityManager {
public:
	EntityManager(SystemManager* systemManager, TextureManager* textureManager);
	~EntityManager();

	int AddEntity(const Bitmask& mask);
	int AddEntity(const std::string& entityFile);
	bool RemoveEntity(const EntityId& id);

	bool AddComponent(const EntityId& entity, const Component& component);

	template <class T>
	T* GetComponent(const EntityId& entity, const Component& component) {
		auto iter = m_entities.find(entity);
		if (iter == m_entities.end()) return nullptr;

		if (!iter->second.first.GetBit(static_cast<unsigned int>(component))) return nullptr;

		auto& container = iter->second.second;
		auto compIter = std::find_if(container.begin(), container.end(),
			[&component](C_Base* c) { return c->GetType() == component; });

		return (compIter != container.end()) ? dynamic_cast<T*>(*compIter) : nullptr;
	}

	bool RemoveComponent(const EntityId& entity, const Component& component);
	bool HasComponent(const EntityId& entity, const Component& component);

	void Purge();

private:
	template <class T>
	void AddComponentType(const Component& id) {
		m_cFactory[id] = []()->C_Base* { return new T(); };
	}

	// Data members
	unsigned int m_idCounter;
	EntityContainer m_entities;
	ComponentFactory m_cFactory;

	SystemManager* m_systems;
	TextureManager* m_textureManager;
};