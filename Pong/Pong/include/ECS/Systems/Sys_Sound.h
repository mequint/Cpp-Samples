#pragma once

#include "ECS/Components/Comp_SoundEmitter.h"

#include "qe/ECS/Core/Sys_Base.h"

class Sys_Sound : public qe::Sys_Base {
public:
	Sys_Sound(qe::SystemManager* systemManager);
	~Sys_Sound();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entity, const qe::EntityEvent& event);
	void Notify(const qe::Message& message);

	void Setup(qe::AudioManager* audioManager, qe::SoundManager* soundManager);

private:
	qe::AudioManager* m_audioManager;
	qe::SoundManager* m_soundManager;

};