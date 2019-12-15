#include "qe/ECS/S_Base.h"

#include <algorithm>

qe::S_Base::S_Base(const SystemType & id, SystemManager * systemManager) :
	m_id(id),
	m_systemManager(systemManager) {
}

qe::S_Base::~S_Base() {
	cleanup();
}

bool qe::S_Base::addEntity(const EntityId & entityId) {
	if (hasEntity(entityId)) return false;

	m_entities.emplace_back(entityId);
	return true;
}

bool qe::S_Base::hasEntity(const EntityId & entityId) {
	return std::find(m_entities.begin(), m_entities.end(), entityId) != m_entities.end();
}

bool qe::S_Base::removeEntity(const EntityId & entityId) {
	auto entityIter = std::find_if(m_entities.begin(), m_entities.end(), [&entityId](EntityId& id) {
		return id == entityId;
	});

	if (entityIter == m_entities.end()) return false;
	m_entities.erase(entityIter);

	return true;
}

qe::SystemType qe::S_Base::getId() const {
	return m_id;
}

bool qe::S_Base::meetsRequirements(const Bitmask & bits) const {
	return std::find_if(m_requiredComponents.cbegin(), m_requiredComponents.cend(),
		[&bits](const Bitmask& requirements) {
		return (bits & requirements) == (requirements & requirements);		
	}) != m_requiredComponents.cend();
}

void qe::S_Base::cleanup() {
	m_entities.clear();
}