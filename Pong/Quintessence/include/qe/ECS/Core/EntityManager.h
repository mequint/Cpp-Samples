#pragma once

#include <algorithm>
#include <bitset>
#include <functional>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <vector>

#include "qe/ECS/Core/Comp_Base.h"

namespace qe {
	using EntityId = unsigned int;

	using ComponentPtr = std::unique_ptr<Comp_Base>;
	using ComponentContainer = std::vector<ComponentPtr>;

	using Bitmask = std::bitset<static_cast<size_t>(Component::COUNT)>;
	using EntityData = std::pair<Bitmask, ComponentContainer>;
	using EntityContainer = std::unordered_map<EntityId, EntityData>;
	using ComponentFactory = std::unordered_map<Component, std::function<Comp_Base*(void)>>;

	// Forward declaration
	class SystemManager;

	class EntityManager
	{
		public:
			EntityManager(SystemManager* systemManager);
			~EntityManager();

			int AddEntity(const Bitmask& mask);
			bool RemoveEntity(const EntityId& id);

			bool AddComponent(const EntityId& entityId, const Component& component);
			bool RemoveComponent(const EntityId& entityId, const Component& component);
			bool HasComponent(const EntityId& entityId, const Component& component);

			template <class T>
			void RegisterComponent(const Component& id) {
				m_componentFactory[id] = []()->Comp_Base* { return new T(); };
			}

			template <class T>
			T* GetComponent(const EntityId& entity, const Component& component) {
				auto iter = m_entities.find(entity);
				if (iter == m_entities.end()) return nullptr;

				if (!iter->second.first[static_cast<size_t>(component)]) return nullptr;

				auto& container = iter->second.second;
				auto compIter = std::find_if(container.begin(), container.end(), 
					[&component](ComponentPtr& c)
				{
					return c->GetType() == component;
				});

				return (compIter != container.end()) ? dynamic_cast<T*>(&(*compIter->get())) : nullptr;
			}

			void Cleanup();

			int GetFirstEntityId() const;
			int GetLastEntityId() const;

		protected:
			unsigned int m_idCounter;
			EntityContainer m_entities;
			ComponentFactory m_componentFactory;

			SystemManager* m_systemManager;
	};
}