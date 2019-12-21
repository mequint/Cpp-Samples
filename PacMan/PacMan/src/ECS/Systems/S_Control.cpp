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

void S_Control::notify(const qe::Message & message) {}
void S_Control::update(float dt) {}

void S_Control::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
	auto entityManager = m_systemManager->getEntityManager();
	
	auto motion = entityManager->getComponent<C_Motion>(entityId, static_cast<qe::ComponentType>(Component::Motion));

	switch (static_cast<EntityEvent>(event)) {
		case EntityEvent::Moving_Up:
			motion->setVelocity(0.0f, -128.0f);
			break;
		case EntityEvent::Moving_Down:
			motion->setVelocity(0.0f, 128.0f);
			break;

		case EntityEvent::Moving_Left:
			motion->setVelocity(-128.0f, 0.0f);
			break;

		case EntityEvent::Moving_Right:
			motion->setVelocity(128.0f, 0.0f);
			break;
	}
}