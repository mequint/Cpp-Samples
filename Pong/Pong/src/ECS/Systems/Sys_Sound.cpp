#include "ECS/Systems/Sys_Sound.h"

#include "qe/ECS/Core/SystemManager.h"

Sys_Sound::Sys_Sound(qe::SystemManager* systemManager) : 
	Sys_Base(System::Sound, systemManager),
	m_audioManager(nullptr),
	m_soundManager(nullptr) {

	qe::Bitmask req;
	req.set(static_cast<size_t>(Component::SoundEmitter));
	m_requiredComponents.push_back(req);
}

Sys_Sound::~Sys_Sound() = default;

void Sys_Sound::Update(float dt) {}

void Sys_Sound::HandleEvent(const qe::EntityId& entity, const qe::EntityEvent& event) {
	switch (event) {
		case qe::EntityEvent::Collision_X: {
			if (!HasEntity(entity)) return;
			if (!m_systemManager->GetEntityManager()->HasComponent(entity, Component::SoundEmitter)) return;

			auto entities = m_systemManager->GetEntityManager();

			auto soundComponent = entities->GetComponent<Comp_SoundEmitter>(entity, Component::SoundEmitter);
			m_soundManager->Play(soundComponent->GetSound(EntitySound::Collision), false, false);

			break;
		}
	}
}

void Sys_Sound::Notify(const qe::Message& message) {}

void Sys_Sound::Setup(qe::AudioManager* audioManager, qe::SoundManager* soundManager) {
	m_audioManager = audioManager;
	m_soundManager = soundManager;
}