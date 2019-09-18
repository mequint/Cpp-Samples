#pragma once

#include "qe/ECS/Core/Sys_Base.h"

// Consumes an X Out of Bounds event taking a Direction, and adds a point to that side
class Sys_GameData : public qe::Sys_Base {
public:
	Sys_GameData(qe::SystemManager* systemManager);

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entityId, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);

	void SetLeftEntity(int id);
	void SetRightEntity(int id);

	void Reset();

private:
	int m_leftEntity;
	int m_rightEntity;

	int m_leftPoints;
	int m_rightPoints;
};