#include "Enemy.h"

Enemy::Enemy(EntityManager * entityManager) : 
	Character(entityManager),
	m_hasDestination(false){
	m_type = EntityType::Enemy;
}

Enemy::~Enemy() = default;

void Enemy::OnEntityCollision(EntityBase * collider, bool attack) {
	if (m_state == EntityState::Dying) return;
	if (attack) return;
	if (collider->GetType() != EntityType::Player) return;

	Character* player = dynamic_cast<Character*>(collider);

	SetState(EntityState::Attacking);
	player->GetHurt(1);

	if (m_position.x > player->GetPosition().x) {
		player->AddVelocity(-m_speed.x, 0.0f);
		m_spriteSheet.SetDirection(Direction::Left);
	}
	else {
		player->AddVelocity(m_speed.y, 0.0f);
		m_spriteSheet.SetDirection(Direction::Right);
	}
}

void Enemy::Update(float dt) {
	Character::Update(dt);

	// Move to destination
	if (m_hasDestination) {
		if (abs(m_destination.x - m_position.x) < 16.0f) {
			m_hasDestination = false;
			return;
		}

		if (m_destination.x - m_position.x > 0.0f) {
			Move(Direction::Right);
		}
		else {
			Move(Direction::Left);
		}

		if (m_collidingOnX) {
			m_hasDestination = false;
		}

		return;
	}

	// Determine a new destination
	int random = rand() % 1000 + 1;
	if (random != 1000) return;

	int newX = rand() % 65;
	if (rand() % 2) {
		newX = -newX;
	}

	m_destination.x = m_position.x + newX;

	if (m_destination.x < 0.0f) {
		m_destination.x = 0;
	}

	m_hasDestination = true;
}