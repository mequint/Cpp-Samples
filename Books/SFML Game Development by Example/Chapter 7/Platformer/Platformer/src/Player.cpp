#include "Player.h"

#include "EventManager.h"
#include "EntityManager.h"
#include "SharedContext.h"
#include "StateManager.h"

Player::Player(EntityManager* entityManager) :
	Character(entityManager) {

	Load("Player.char");
	m_type = EntityType::Player;

	EventManager* events = m_entityManager->GetContext()->m_eventManager;
	events->AddCallback<Player>(StateType::Game, "Player_MoveLeft", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_MoveRight", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_Jump", &Player::React, this);
	events->AddCallback<Player>(StateType::Game, "Player_Attack", &Player::React, this);
}

Player::~Player() {
	EventManager* events = m_entityManager->GetContext()->m_eventManager;
	events->RemoveCallback(StateType::Game, "Player_MoveLeft");
	events->RemoveCallback(StateType::Game, "Player_MoveRight");
	events->RemoveCallback(StateType::Game, "Player_Jump");
	events->RemoveCallback(StateType::Game, "Player_Attack");
}

void Player::OnEntityCollision(EntityBase* collider, bool attack) {
	if (m_state == EntityState::Dying) return;

	if (attack) {
		if (m_state != EntityState::Attacking) return;
		if (!m_spriteSheet.GetCurrentAnim()->IsInAction()) return;

		if (collider->GetType() != EntityType::Enemy &&
			collider->GetType() != EntityType::Player) {
			return;
		}

		Character* opponent = dynamic_cast<Character*>(collider);
		opponent->GetHurt(1);

		if (m_position.x > opponent->GetPosition().x) {
			opponent->AddVelocity(-32.0f, 0.0f);
		}
		else {
			opponent->AddVelocity(32.0f, 0.0f);
		}
	}
}

void Player::React(EventDetails * details) {
	if (details->m_name == "Player_MoveLeft") {
		Character::Move(Direction::Left);
	}
	else if (details->m_name == "Player_MoveRight") {
		Character::Move(Direction::Right);
	}
	else if (details->m_name == "Player_Jump") {
		Character::Jump();
	}
	else if (details->m_name == "Player_Attack") {
		Character::Attack();
	}
}