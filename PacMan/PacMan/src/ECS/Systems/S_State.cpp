#include "ECS/Systems/S_State.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_EntityType.h"
#include "Utilities/eDirections.h"

#include "qe/ECS/SystemManager.h"

S_State::S_State(qe::SystemManager * systemManager) : 
	S_Base(static_cast<qe::SystemType>(System::State), systemManager) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::EntityType));
	req.set(static_cast<qe::ComponentType>(Component::State));
	m_requiredComponents.push_back(req);
}

S_State::~S_State() = default;

void S_State::notify(const qe::Message & message) {}

void S_State::update(float dt) {}

void S_State::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {}

void S_State::_changeState(const qe::EntityId & entityId, const eEntityState & entityState) {}