#include "qe/ECS/Core/Sys_Base.h"

namespace qe {
	Sys_Base::Sys_Base(const System& id, SystemManager* systemManager) :
		m_id(id),
		m_systemManager(systemManager) {
	}

	Sys_Base::~Sys_Base() {
		Cleanup();
	}

	bool Sys_Base::AddEntity(const EntityId & entityId) {
		if (HasEntity(entityId)) return false;

		m_entities.emplace_back(entityId);
		return true;
	}

	bool Sys_Base::HasEntity(const EntityId & entityId) {
		return std::find(m_entities.begin(), m_entities.end(), entityId) != m_entities.end();
	}

	bool Sys_Base::RemoveEntity(const EntityId & entityId) {
		auto entityIter = std::find_if(m_entities.begin(), m_entities.end(),
			[&entityId](EntityId& id) {
			return id == entityId;
		});

		if (entityIter == m_entities.end()) return false;
		m_entities.erase(entityIter);

		return true;
	}

	System Sys_Base::GetId() const {
		return m_id;
	}

	bool Sys_Base::MeetsRequirements(const Bitmask& bits) const {
		return std::find_if(m_requiredComponents.cbegin(), m_requiredComponents.cend(),
			[&bits](const Bitmask& requirement) {
			return (bits & requirement) == (requirement & requirement);
		}) != m_requiredComponents.cend();

		for (size_t i = 0; i < m_requiredComponents.size(); ++i) {
			auto requirements = m_requiredComponents[i];

			bool fits = true;
			for (size_t j = 0; j < bits.size(); ++j) {
				if (requirements[j] == 1 && bits[i] != 1) {
					return false;
				}

			}
		}

		return true;
	}

	void Sys_Base::Cleanup() {
		m_entities.clear();
	}
}