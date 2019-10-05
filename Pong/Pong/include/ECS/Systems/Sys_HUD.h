#pragma once

#include "qe/ECS/Core//Sys_Base.h"
#include "qe/Window/Window.h"

#include "Views/ProgressBarView.h"

class Sys_HUD : public qe::Sys_Base {
public:
	Sys_HUD(qe::SystemManager* systemManager);
	~Sys_HUD();

	void Setup(const int width, const int height);
	void SetLeftPlayer(const qe::EntityId& entityId);
	void SetRightPlayer(const qe::EntityId & entityId);

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entityId, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);

	void Render(qe::Window* window, unsigned int layer);

private:
	qe::EntityId m_leftPlayer;
	ProgressBarView m_leftHealthBar;
	ProgressBarView m_leftSpecialBar;

	qe::EntityId m_rightPlayer;
	ProgressBarView m_rightHealthBar;
	ProgressBarView m_rightSpecialBar;
};