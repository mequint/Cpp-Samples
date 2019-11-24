#include "EntityManager.h"

#include "SystemManager.h"

EntityManager::EntityManager(SystemManager* systemManager, TextureManager* textureManager) :
	m_idCounter(0),
	m_systems(systemManager),
	m_textureManager(textureManager) {

	AddComponentType<C_Position>(Component::Position);
	AddComponentType<C_SpriteSheet>(Component::SpriteSheet);
	AddComponentType<C_State>(Component::State);
	AddComponentType<C_Movable>(Component::Movable);
	AddComponentType<C_Controller>(Component::Controller);
	AddComponentType<C_Collidable>(Component::Collidable);
	//AddComponentType<C_SoundEmitter>(Component::SoundEmitter);
	//AddComponentType<C_SoundListener>(Component::SoundListener);
}

EntityManager::~EntityManager() {
	Purge();
}

int EntityManager::AddEntity(const Bitmask& mask) {
	unsigned int entity = m_idCounter;
	if (!m_entities.emplace(entity, EntityData(0, ComponentContainer())).second) return -1;

	++m_idCounter;
	for (unsigned int i = 0; i < N_COMPONENT_TYPES; ++i) {
		if (mask.GetBit(i)) {
			AddComponent(entity, static_cast<Component>(i));
		}
	}

	m_systems->EntityModified(entity, mask);
	m_systems->AddEvent(entity, static_cast<EventId>(EntityEvent::Spawned));

	return entity;
}

int EntityManager::AddEntity(const std::string& entityFile) {
	int entityId = -1;

	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + "media/Entities/" + entityFile + ".entity");
	if (!file.is_open()) {
		std::cout << "! Failed to load entity: " << entityFile << std::endl;
		return -1;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "Name") {
			// Do nothing?!? 
		}
		else if (type == "Attributes") {
			if (entityId != -1) continue;

			Bitset set = 0;
			keystream >> set;

			Bitmask mask;
			mask.SetMask(set);

			entityId = AddEntity(mask);
			if (entityId == -1) return -1;
		}
		else if (type == "Component") {
			if (entityId == -1) continue;

			unsigned int cId = 0;
			keystream >> cId;

			C_Base* component = GetComponent<C_Base>(entityId, static_cast<Component>(cId));
			if (!component) continue;

			keystream >> *component;

			if (component->GetType() == Component::SpriteSheet) {
				C_SpriteSheet* sheet = dynamic_cast<C_SpriteSheet*>(component);
				sheet->Create(m_textureManager);
			}
		}
	}

	file.close();
	return entityId;
}

bool EntityManager::RemoveEntity(const EntityId& id) {
	auto iter = m_entities.find(id);
	if (iter == m_entities.end()) return false;

	while (iter->second.second.begin() != iter->second.second.end()) {
		delete iter->second.second.back();
		iter->second.second.pop_back();
	}

	m_entities.erase(iter);
	m_systems->RemoveEntity(id);

	return true;
}

bool EntityManager::AddComponent(const EntityId& entity, const Component& component) {
	auto iter = m_entities.find(entity);
	if (iter == m_entities.end()) return false;

	if (iter->second.first.GetBit(static_cast<unsigned int>(component))) return false;

	auto iter2 = m_cFactory.find(component);
	if (iter2 == m_cFactory.end()) return false;

	C_Base* comp = iter2->second();
	iter->second.second.emplace_back(comp);
	iter->second.first.TurnOnBit(static_cast<unsigned int>(component));

	m_systems->EntityModified(entity, iter->second.first);
	return true;
}

bool EntityManager::RemoveComponent(const EntityId& entity, const Component& component) {
	auto iter = m_entities.find(entity);
	if (iter == m_entities.end()) return false;

	if (!iter->second.first.GetBit(static_cast<unsigned int>(component))) return false;

	auto& container = iter->second.second;
	auto compIter = std::find_if(container.begin(), container.end(),
		[&component](C_Base* c) { return c->GetType() == component; });

	if (compIter == container.end()) return false;

	delete (*compIter);
	container.erase(compIter);

	iter->second.first.ClearBit(static_cast<unsigned int>(component));

	m_systems->EntityModified(entity, iter->second.first);
	return true;
}

bool EntityManager::HasComponent(const EntityId& entity, const Component& component) {
	auto iter = m_entities.find(entity);
	if (iter == m_entities.end()) return false;

	return iter->second.first.GetBit(static_cast<unsigned int>(component));
}

void EntityManager::Purge() {
	m_systems->PurgeEntities();

	for (auto& entity : m_entities) {
		for (auto& component : entity.second.second) delete component;

		entity.second.second.clear();
		entity.second.first.Clear();
	}

	m_entities.clear();
	m_idCounter = 0;
}