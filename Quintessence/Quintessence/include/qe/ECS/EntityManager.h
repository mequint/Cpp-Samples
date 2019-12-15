#pragma once

#include <bitset>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "C_Base.h"

namespace qe {
	using EntityId = unsigned int;

	using ComponentPtr = std::unique_ptr<C_Base>;
	using ComponentContainer = std::vector<ComponentPtr>;

	// NOTE: Limit the max number of components to 32 (for now...)
	using Bitmask = std::bitset<static_cast<ComponentType>(32)>;
	using EntityData = std::pair<Bitmask, ComponentContainer>;

	using EntityContainer = std::unordered_map<EntityId, EntityData>;
	using ComponentFactory = std::unordered_map<ComponentType, std::function<C_Base*(void)>>;

	class SystemManager;

	class EntityManager {
	public:
		EntityManager(SystemManager* systemManager);
		virtual ~EntityManager();

		virtual int addEntity(const Bitmask& mask);
		bool removeEntity(const EntityId& entityId);

		bool addComponent(const EntityId& entityId, const ComponentType& component);
		bool removeComponent(const EntityId& entityId, const ComponentType& component);
		bool hasComponent(const EntityId& entityId, const ComponentType& component);


		template <class T>
		void registerComponent(const ComponentType& id) {
			m_componentFactory[id] = []()->C_Base* {
				return new T();
			};
		}

		template <class T>
		T* getComponent(const EntityId& entityId, const ComponentType& component) {
			auto iter = m_entities.find(entityId);
			if (iter == m_entities.end()) return nullptr;

			if (!iter->second.first[component]) return nullptr;

			auto& container = iter->second.second;
			auto compIter = std::find_if(container.begin(), container.end(), 
				[&component](ComponentPtr& c) {
				return c->getType() == component;
			});

			return (compIter != container.end()) ? dynamic_cast<T*>(&(*compIter->get())) : nullptr;
		}

		void cleanup();

	protected:
		unsigned int m_idCounter;
		EntityContainer m_entities;
		ComponentFactory m_componentFactory;

		SystemManager* m_systemManager;
	};
}