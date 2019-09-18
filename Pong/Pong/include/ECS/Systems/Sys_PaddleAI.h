#pragma once

#include "qe/ECS/Core/Sys_Base.h"

class Sys_PaddleAI : public qe::Sys_Base {
public:
	Sys_PaddleAI(qe::SystemManager* systemManager);
	~Sys_PaddleAI();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entityId, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);

	void SetPaddle(const qe::EntityId& entityId);
	void SetBall(const qe::EntityId& entityId);

private:
	qe::EntityId m_paddleId;
	qe::EntityId m_ballId;
};