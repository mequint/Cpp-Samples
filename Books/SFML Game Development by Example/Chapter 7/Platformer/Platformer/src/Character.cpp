#include "Character.h"

#include "DebugOverlay.h"
#include "EntityManager.h"
#include "SharedContext.h"

Character::Character(EntityManager* entityManager) :
	EntityBase(entityManager), 
	m_spriteSheet(entityManager->GetContext()->m_textureManager),
	m_jumpVelocity(250.0f),
	m_hitpoints(5) {

	m_name = "Character";
}

Character::~Character() = default;

void Character::Move(const Direction& dir) {
	if (GetState() == EntityState::Dying) return;

	m_spriteSheet.SetDirection(dir);

	if (dir == Direction::Left) {
		Accelerate(-m_speed.x, 0.0f);
	}
	else {
		Accelerate(m_speed.x, 0.0f);
	}

	if (GetState() == EntityState::Idle) {
		SetState(EntityState::Walking);
	}
}

void Character::Jump() {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping || GetState() == EntityState::Hurt) return;

	SetState(EntityState::Jumping);
	AddVelocity(0.0f, -m_jumpVelocity);
}

void Character::Attack() {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Jumping ||
		GetState() == EntityState::Hurt || GetState() == EntityState::Attacking) {
		return;
	}

	SetState(EntityState::Attacking);
}

void Character::GetHurt(int damage) {
	if (GetState() == EntityState::Dying || GetState() == EntityState::Hurt) return;

	m_hitpoints = (m_hitpoints - damage > 0 ? m_hitpoints - damage : 0);

	if (m_hitpoints) {
		SetState(EntityState::Hurt);
	}
	else {
		SetState(EntityState::Dying);
	}
}

void Character::Load(const std::string & path) {
	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + std::string("media/Characters/") + path);
	if (!file.is_open()) {
		std::cout << "! Failed to load the character file: " << path << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') continue;

		std::stringstream keystream(line);
		std::string type;
		keystream >> type;

		if (type == "Name") {
			keystream >> m_name;
		}
		else if (type == "Spritesheet") {
			std::string path;
			keystream >> path;

			m_spriteSheet.LoadSheet("media/SpriteSheets/" + path);
		}
		else if (type == "Hitpoints") {
			keystream >> m_hitpoints;
		}
		else if (type == "BoundingBox") {
			sf::Vector2f boundingSize;
			keystream >> boundingSize.x >> boundingSize.y;

			SetSize(boundingSize.x, boundingSize.y);
		}
		else if (type == "DamageBox") {
			keystream >> m_attackAABBoffset.x >> m_attackAABBoffset.y >> m_attackAABB.width >> m_attackAABB.height;
		}
		else if (type == "Speed") {
			keystream >> m_speed.x >> m_speed.y;
		}
		else if (type == "JumpVelocity") {
			keystream >> m_jumpVelocity;
		}
		else if (type == "MaxVelocity") {
			keystream >> m_maxVelocity.x >> m_maxVelocity.y;
		}
		else {
			std::cout << "! Unknown type in character file: " << type << std::endl;
		}
	}

	file.close();
}

void Character::Update(float dt) {
	EntityBase::Update(dt);
	if (m_attackAABB.width != 0.0f && m_attackAABB.height != 0.0f) {
		UpdateAttackAABB();

		// Debug
		if (m_entityManager->GetContext()->m_debugOverlay->Debug()) {
			sf::RectangleShape* arect = new sf::RectangleShape(sf::Vector2f(m_attackAABB.width, m_attackAABB.height));
			arect->setPosition(m_attackAABB.left, m_attackAABB.top);
			arect->setFillColor(sf::Color(255, 0, 0, (m_state == EntityState::Attacking && m_spriteSheet.GetCurrentAnim()->IsInAction() ?
				200 : 100)));

			m_entityManager->GetContext()->m_debugOverlay->Add(arect);
		}
		// End Debug
	}

	if (GetState() != EntityState::Dying && GetState() != EntityState::Attacking && GetState() != EntityState::Hurt) {
		if (abs(m_velocity.y) >= 0.001f) {
			SetState(EntityState::Jumping);
		}
		else if (abs(m_velocity.x) >= 0.1f) {
			SetState(EntityState::Walking);
		}
		else {
			SetState(EntityState::Idle);
		}
	}
	else if (GetState() == EntityState::Attacking || GetState() == EntityState::Hurt) {
		if (!m_spriteSheet.GetCurrentAnim()->IsPlaying()) {
			SetState(EntityState::Idle);
		}
	}
	else if (GetState() == EntityState::Dying) {
		if (!m_spriteSheet.GetCurrentAnim()->IsPlaying()) {
			m_entityManager->Remove(m_id);
		}
	}

	Animate();

	m_spriteSheet.Update(dt);
	m_spriteSheet.SetSpritePosition(m_position);
}

void Character::Draw(sf::RenderWindow * window) {
	m_spriteSheet.Draw(window);
}

void Character::UpdateAttackAABB() {
	m_attackAABB.left = (m_spriteSheet.GetDirection() == Direction::Left ?
		(m_AABB.left - m_attackAABB.width) - m_attackAABBoffset.x :
		(m_AABB.left + m_AABB.width) + m_attackAABBoffset.x);

	m_attackAABB.top = m_AABB.top + m_attackAABBoffset.y;
}

void Character::Animate() {
	EntityState state = GetState();
	std::string animName = m_spriteSheet.GetCurrentAnim()->GetName();

	if (state == EntityState::Walking && animName != "Walk") {
		m_spriteSheet.SetAnimation("Walk", true, true);
	}
	else if (state == EntityState::Jumping && animName != "Jump") {
		m_spriteSheet.SetAnimation("Jump", true, false);
	}
	else if (state == EntityState::Attacking && animName != "Attack") {
		m_spriteSheet.SetAnimation("Attack", true, false);
	}
	else if (state == EntityState::Hurt && animName != "Hurt") {
		m_spriteSheet.SetAnimation("Hurt", true, false);
	}
	else if (state == EntityState::Dying && animName != "Death") {
		m_spriteSheet.SetAnimation("Death", true, false);
	}
	else if (state == EntityState::Idle && animName != "Idle") {
		m_spriteSheet.SetAnimation("Idle", true, true);
	}
}
