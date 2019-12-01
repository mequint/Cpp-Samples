#include "S_Movement.h"

#include "SystemManager.h"
#include "Map.h"

S_Movement::S_Movement(SystemManager * systemManager) :
	S_Base(System::Movement, systemManager) {

	Bitmask req;
	req.TurnOnBit(static_cast<unsigned int>(Component::Position));
	req.TurnOnBit(static_cast<unsigned int>(Component::Movable));
	m_requiredComponents.push_back(req);
	req.Clear();

	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Is_Moving, this);

	m_gameMap = nullptr;
}

S_Movement::~S_Movement() = default;

void S_Movement::Update(float dt) {
	if (!m_gameMap) return;

	EntityManager* entities = m_systemManager->GetEntityManager();
	for (auto& entity : m_entities) {
		C_Position* position = entities->GetComponent<C_Position>(entity, Component::Position);
		C_Movable* movable = entities->GetComponent<C_Movable>(entity, Component::Movable);

		MovementStep(dt, movable, position);
		position->MoveBy(movable->GetVelocity() * dt);
	}
}

void S_Movement::HandleEvent(const EntityId & entity, const EntityEvent & event) {
	switch (event) {
		case EntityEvent::Colliding_X: StopEntity(entity, Axis::x); break;
		case EntityEvent::Colliding_Y: StopEntity(entity, Axis::y); break;
		case EntityEvent::Moving_Left: SetDirection(entity, Direction::Left); break;
		case EntityEvent::Moving_Right: SetDirection(entity, Direction::Right); break;
		
		case EntityEvent::Moving_Up: {
			C_Movable* mov = m_systemManager->GetEntityManager()->GetComponent<C_Movable>(entity, Component::Movable);
			if (mov->GetVelocity().x == 0) {
				SetDirection(entity, Direction::Up);
			}
			break;
		}

		case EntityEvent::Moving_Down: {
			C_Movable* mov = m_systemManager->GetEntityManager()->GetComponent<C_Movable>(entity, Component::Movable);
			if (mov->GetVelocity().x == 0) {
				SetDirection(entity, Direction::Down);
			}
			break;
		}
	}
}

void S_Movement::Notify(const Message & message) {
	EntityManager* entityManager = m_systemManager->GetEntityManager();
	EntityMessage m = static_cast<EntityMessage>(message.m_type);

	switch (m) {
		case EntityMessage::Is_Moving: {
			if (!HasEntity(message.m_receiver)) return;

			C_Movable* movable = entityManager->GetComponent<C_Movable>(message.m_receiver, Component::Movable);

			if (movable->GetVelocity() != sf::Vector2f(0.0f, 0.0f)) return;

			m_systemManager->AddEvent(message.m_receiver, static_cast<EventId>(EntityEvent::Became_Idle));

			break;
		}
	}
}

void S_Movement::SetMap(Map * gameMap) { m_gameMap = gameMap; }

void S_Movement::StopEntity(const EntityId & entity, const Axis & axis) {
	C_Movable* movable = m_systemManager->GetEntityManager()->GetComponent<C_Movable>(entity, Component::Movable);
	
	if (axis == Axis::x) {
		movable->SetVelocity(sf::Vector2f(0.0f, movable->GetVelocity().y));
	}
	else if (axis == Axis::y) {
		movable->SetVelocity(sf::Vector2f(movable->GetVelocity().x, 0.0f));
	}
}

void S_Movement::SetDirection(const EntityId & entity, const Direction & dir) {
	C_Movable* movable = m_systemManager->GetEntityManager()->GetComponent<C_Movable>(entity, Component::Movable);
	movable->SetDirection(dir);

	Message msg(static_cast<MessageType>(EntityMessage::Direction_Changed));
	msg.m_receiver = entity;
	msg.m_int = static_cast<int>(dir);
	
	m_systemManager->GetMessageHandler()->Dispatch(msg);
}

const sf::Vector2f & S_Movement::GetTileFriction(unsigned int elevation, unsigned int x, unsigned int y) {
	Tile* t = nullptr;
	while (!t && elevation >= 0) {
		t = m_gameMap->GetTile(x, y, elevation);
		--elevation;
	}

	return (t ? t->m_properties->m_friction : m_gameMap->GetDefaultTile()->m_friction);
}

void S_Movement::MovementStep(float dt, C_Movable * movable, C_Position * position) {
	sf::Vector2f fCoefficient = GetTileFriction(position->GetElevation(),
		static_cast<unsigned int>(floor(position->GetPosition().x / Sheet::Tile_Size)),
		static_cast<unsigned int>(floor(position->GetPosition().y / Sheet::Tile_Size)));

	sf::Vector2f friction(movable->GetSpeed().x * fCoefficient.x, movable->GetSpeed().y * fCoefficient.y);

	movable->AddVelocity(movable->GetAcceleration() * dt);
	movable->SetAcceleration(sf::Vector2f(0.0f, 0.0f));
	movable->ApplyFriction(friction * dt);

	float magnitude = sqrt(movable->GetVelocity().x * movable->GetVelocity().x +
		movable->GetVelocity().y * movable->GetVelocity().y);

	if (magnitude <= movable->GetMaxVelocity()) return;

	float maxV = movable->GetMaxVelocity();
	movable->SetVelocity(sf::Vector2f(
		(movable->GetVelocity().x / magnitude) * maxV, 
		(movable->GetVelocity().y / magnitude) * maxV));
}