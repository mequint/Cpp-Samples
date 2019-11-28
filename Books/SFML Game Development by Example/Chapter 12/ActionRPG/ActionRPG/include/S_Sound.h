#pragma once

#include "S_Base.h"
#include "C_SoundEmitter.h"
#include "C_SoundListener.h"

class S_Sound : public S_Base {
public:
	S_Sound(SystemManager* systemManager);
	~S_Sound();

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);

	void SetUp(AudioManager* audioManager, SoundManager* soundManager);

private:
	sf::Vector3f MakeSoundPosition(const sf::Vector2f& entityPos, unsigned int elevation);
	void EmitSound(const EntityId& entity, const EntitySound& sound, bool useId, bool relative, int checkFrame = -1);

	AudioManager* m_audioManager;
	SoundManager* m_soundManager;
};