#include "ECS/Systems/Sys_PaddleAI.h"

#include "qe/ECS/Core/SystemManager.h"

#include "ECS/Components/Comp_Collider.h"
#include "ECS/Components/Comp_Motion.h"
#include "ECS/Components/Comp_Position.h"

Sys_PaddleAI::Sys_PaddleAI(qe::SystemManager* systemManager) : Sys_Base(System::PaddleAI, systemManager) {
	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::AIController));
	
	m_requiredComponents.push_back(req);
}

Sys_PaddleAI::~Sys_PaddleAI() = default;

void Sys_PaddleAI::Update(float dt) {
	auto entityManager = m_systemManager->GetEntityManager();
	auto ballPosition = entityManager->GetComponent<Comp_Position>(m_ballId, Component::Position);
	auto ballPosDelta = ballPosition->GetPosition() - ballPosition->GetOldPosition();

	auto paddleMotion = entityManager->GetComponent<Comp_Motion>(m_paddleId, Component::Motion);

	// Ball is incoming...move to intercept
	if (ballPosDelta.x > 0.0f) {
		auto paddlePosition = entityManager->GetComponent<Comp_Position>(m_paddleId, Component::Position);
		auto paddleCollider = entityManager->GetComponent<Comp_Collider>(m_paddleId, Component::Collider);

		if (ballPosition->GetPosition().y > paddlePosition->GetPosition().y + paddleCollider->GetAABB().height / 2.0f) {
			paddleMotion->SetVelocity(sf::Vector2f(0.0f, 128.0f));
		}
		else if (ballPosition->GetPosition().y < paddlePosition->GetPosition().y + paddleCollider->GetAABB().height / 2.0f) {
			paddleMotion->SetVelocity(sf::Vector2f(0.0f, -128.0f));
		}
		else {
			paddleMotion->SetVelocity(sf::Vector2f(0.0f, 0.0f));
		}
	}
	// Ball is moving away...hold still
	else {
		paddleMotion->SetVelocity(sf::Vector2f(0.0f, 0.0f));
	}
}

void Sys_PaddleAI::HandleEvent(const qe::EntityId & entityId, const qe::EntityEvent & event) {
}

void Sys_PaddleAI::Notify(const qe::Message & message) {
}

void Sys_PaddleAI::SetPaddle(const qe::EntityId & entityId) {
	m_paddleId = entityId;
}

void Sys_PaddleAI::SetBall(const qe::EntityId & entityId) {
	m_ballId = entityId;
}