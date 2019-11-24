#include "S_Control.h"

#include "SystemManager.h"

S_Control::S_Control(SystemManager * systemManager) :
	S_Base(System::Control, systemManager) {
	Bitmask req;
	req.TurnOnBit(static_cast<unsigned int>(Component::Position));
	req.TurnOnBit(static_cast<unsigned int>(Component::Movable));
	req.TurnOnBit(static_cast<unsigned int>(Component::Controller));
	m_requiredComponents.push_back(req);

	req.Clear();
}

S_Control::~S_Control() {}

void S_Control::Update(float dt) {}

void S_Control::HandleEvent(const EntityId & entity, const EntityEvent & event) {
	switch (event) {
		case EntityEvent::Moving_Left: MoveEntity(entity, Direction::Left); break;
		case EntityEvent::Moving_Right: MoveEntity(entity, Direction::Right); break;
		case EntityEvent::Moving_Up: MoveEntity(entity, Direction::Up); break;
		case EntityEvent::Moving_Down: MoveEntity(entity, Direction::Down); break;
	}
}

void S_Control::Notify(const Message & message) {}

void S_Control::MoveEntity(const EntityId & entity, const Direction & dir) {
	C_Movable* mov = m_systemManager->GetEntityManager()->GetComponent<C_Movable>(entity, Component::Movable);
	mov->Move(dir);
}