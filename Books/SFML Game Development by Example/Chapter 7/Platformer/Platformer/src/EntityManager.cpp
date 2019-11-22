#include "EntityManager.h"

#include "SharedContext.h"
#include "Window.h"

EntityManager::EntityManager(SharedContext * context, unsigned int maxEntities) :
	m_context(context), m_maxEntities(maxEntities), m_idCounter(0) {

	LoadEnemyTypes("EnemyList.list");
	RegisterEntity<Player>(EntityType::Player);
	RegisterEntity<Enemy>(EntityType::Enemy);
}

EntityManager::~EntityManager() {
	Purge();
}

int EntityManager::Add(const EntityType & type, const std::string & name) {
	auto iter = m_entityFactory.find(type);
	if (iter == m_entityFactory.end()) return -1;

	EntityBase* entity = iter->second();
	entity->m_id = m_idCounter;
	
	if (name != "") { 
		entity->m_name = name; 
	}

	m_entities.emplace(m_idCounter, entity);

	if (type == EntityType::Enemy) {
		auto iter = m_enemyTypes.find(name);
		if (iter != m_enemyTypes.end()) {
			Enemy* enemy = dynamic_cast<Enemy*>(entity);
			enemy->Load(iter->second);
		}
	}

	++m_idCounter;

	return m_idCounter - 1;
}

EntityBase * EntityManager::Find(unsigned int id) {
	auto iter = m_entities.find(id);
	if (iter == m_entities.end()) return nullptr;

	return iter->second;
}

EntityBase * EntityManager::Find(const std::string & name) {
	for (auto& iter : m_entities) {
		if (iter.second->GetName() == name) {
			return iter.second;
		}
	}

	return nullptr;
}

void EntityManager::Remove(unsigned int id) {
	m_entitiesToRemove.emplace_back(id);
}

void EntityManager::Update(float dt) {
	for (auto& iter : m_entities) {
		iter.second->Update(dt);
	}

	EntityCollisionCheck();
	ProcessRemovals();
}

void EntityManager::Draw() {
	sf::RenderWindow* window = m_context->m_window->GetRenderWindow();
	sf::FloatRect viewSpace = m_context->m_window->GetViewSpace();

	for (auto& iter : m_entities) {
		if (!viewSpace.intersects(iter.second->m_AABB)) continue;

		iter.second->Draw(window);
	}
}

void EntityManager::Purge() {
	for (auto& iter : m_entities) {
		delete iter.second;
	}

	m_entities.clear();
	m_idCounter = 0;
}

SharedContext * EntityManager::GetContext() {
	return m_context;
}

void EntityManager::ProcessRemovals() {
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end()) {
		unsigned int id = m_entitiesToRemove.back();
		auto iter = m_entities.find(id);

		if (iter != m_entities.end()) {
			std::cout << "Discarding entity: " << iter->second->GetId() << std::endl;
			delete iter->second;
			m_entities.erase(iter);
		}

		m_entitiesToRemove.pop_back();
	}
}

void EntityManager::LoadEnemyTypes(const std::string & name) {
	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + std::string("media/Characters/") + name);

	if (!file.is_open()) {
		std::cout << "! Failed to load file: " << name << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string name;
		std::string charFile;

		keystream >> name >> charFile;

		m_enemyTypes.emplace(name, charFile);
	}

	file.close();
}

void EntityManager::EntityCollisionCheck() {
	if (m_entities.empty()) return;

	for (auto iter1 = m_entities.begin(); std::next(iter1) != m_entities.end(); ++iter1) {
		for (auto iter2 = std::next(iter1); iter2 != m_entities.end(); ++iter2) {
			if (iter1->first == iter2->first) continue;

			if (iter1->second->m_AABB.intersects(iter2->second->m_AABB)) {
				iter1->second->OnEntityCollision(iter2->second, false);
				iter2->second->OnEntityCollision(iter1->second, false);
			}

			EntityType t1 = iter1->second->GetType();
			EntityType t2 = iter2->second->GetType();

			if (t1 == EntityType::Player || t1 == EntityType::Enemy) {
				Character* c1 = dynamic_cast<Character*>(iter1->second);
				if (c1->m_attackAABB.intersects(iter2->second->m_AABB)) {
					c1->OnEntityCollision(iter2->second, true);
				}
			}

			if (t2 == EntityType::Player || t2 == EntityType::Enemy) {
				Character* c2 = dynamic_cast<Character*>(iter2->second);
				if (c2->m_attackAABB.intersects(iter1->second->m_AABB)) {
					c2->OnEntityCollision(iter1->second, true);
				}
			}
		}
	}
}