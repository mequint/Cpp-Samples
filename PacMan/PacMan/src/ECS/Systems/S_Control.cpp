#include "ECS/Systems/S_Control.h"

#include "qe/ECS/SystemManager.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/C_Controller.h"
#include "ECS/Components/C_Motion.h"

S_Control::S_Control(qe::SystemManager* systemManager) :
	S_Base(static_cast<qe::SystemType>(System::Control), systemManager) {

	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Controller));
	req.set(static_cast<qe::ComponentType>(Component::Motion));
	m_requiredComponents.push_back(req);
}

S_Control::~S_Control() = default;

void S_Control::notify(const qe::Message & message) {

}
void S_Control::update(float dt) {}

void S_Control::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
}