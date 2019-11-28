#include "S_Sound.h"

#include "Map.h"					// NOTE: Used for one function...figure out how to break this out...
#include "SystemManager.h"

S_Sound::S_Sound(SystemManager * systemManager) : 
	S_Base(System::Sound, systemManager),
	m_audioManager(nullptr),
	m_soundManager(nullptr) {

	Bitmask req;
	req.TurnOnBit(static_cast<unsigned int>(Component::Position));
	req.TurnOnBit(static_cast<unsigned int>(Component::SoundEmitter));
	m_requiredComponents.push_back(req);

	req.ClearBit(static_cast<unsigned int>(Component::SoundEmitter));
	req.TurnOnBit(static_cast<unsigned int>(Component::SoundListener));
	m_requiredComponents.push_back(req);

	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Direction_Changed, this);
	m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Frame_Change, this);
}

S_Sound::~S_Sound() = default;

void S_Sound::Update(float dt) {
	EntityManager* entities = m_systemManager->GetEntityManager();

	for (auto& entity : m_entities) {
		C_Position* cPos = entities->GetComponent<C_Position>(entity, Component::Position);
		sf::Vector2f position = cPos->GetPosition();
		unsigned int elevation = cPos->GetElevation();

		bool isListener = entities->HasComponent(entity, Component::SoundListener);
		if (isListener) {
			sf::Listener::setPosition(MakeSoundPosition(position, elevation));
		}

		if (!entities->HasComponent(entity, Component::SoundEmitter)) continue;

		C_SoundEmitter* cSnd = entities->GetComponent<C_SoundEmitter>(entity, Component::SoundEmitter);
		if (cSnd->GetSoundID() == -1) continue;

		if (!isListener) {
			if (!m_soundManager->SetPosition(cSnd->GetSoundID(), MakeSoundPosition(position, elevation))) {
				cSnd->SetSoundID(-1);
			}
			else {
				if (!m_soundManager->IsPlaying(cSnd->GetSoundID())) {
					cSnd->SetSoundID(-1);
				}
			}
		}
	}
}

void S_Sound::HandleEvent(const EntityId & entity, const EntityEvent & event) {}

void S_Sound::Notify(const Message & message) {
	if (!HasEntity(message.m_receiver)) return;

	EntityManager* entities = m_systemManager->GetEntityManager();
	
	bool isListener = entities->HasComponent(message.m_receiver, Component::SoundListener);

	EntityMessage m = static_cast<EntityMessage>(message.m_type);
	switch (m) {
		case EntityMessage::Direction_Changed: {
			if (!isListener) return;

			Direction dir = static_cast<Direction>(message.m_int);

			switch (dir) {
				case Direction::Up: sf::Listener::setDirection(0.0f, 0.0f, -1.0f); break;
				case Direction::Down: sf::Listener::setDirection(0.0f, 0.0f, 1.0f); break;
				case Direction::Left: sf::Listener::setDirection(-1.0f, 0.0f, 0.0f); break;
				case Direction::Right: sf::Listener::setDirection(1.0f, 0.0f, 0.0f); break;
			}

			break;
		}

		case EntityMessage::Frame_Change: {
			if (!entities->HasComponent(message.m_receiver, Component::SoundEmitter)) return;

			EntityState state = entities->GetComponent<C_State>(message.m_receiver, Component::State)->GetState();
			EntitySound sound = EntitySound::None;

			if (state == EntityState::Walking) {
				sound = EntitySound::Footstep;
			}
			else if (state == EntityState::Attacking) {
				sound = EntitySound::Attack;
			}
			else if (state == EntityState::Hurt) {
				sound = EntitySound::Hurt;
			}
			else if (state == EntityState::Dying) {
				sound = EntitySound::Death;
			}

			if (sound == EntitySound::None) return;

			EmitSound(message.m_receiver, sound, false, isListener, message.m_int);

			break;
		}
	}
}

void S_Sound::SetUp(AudioManager * audioManager, SoundManager * soundManager) {
	m_audioManager = audioManager;
	m_soundManager = soundManager;
}

sf::Vector3f S_Sound::MakeSoundPosition(const sf::Vector2f & entityPos, unsigned int elevation) {
	return sf::Vector3f(entityPos.x, static_cast<float>(elevation * Sheet::Tile_Size), entityPos.y);
}

void S_Sound::EmitSound(const EntityId & entity, const EntitySound & sound, bool useId, bool relative, int checkFrame) {
	if (!HasEntity(entity)) return;
	if (!m_systemManager->GetEntityManager()->HasComponent(entity, Component::SoundEmitter)) return;

	EntityManager* entities = m_systemManager->GetEntityManager();
	C_SoundEmitter* cSnd = entities->GetComponent<C_SoundEmitter>(entity, Component::SoundEmitter);

	if (cSnd->GetSoundID() != -1 && useId) return;
	if (checkFrame != -1 && cSnd->IsSoundFrame(sound, checkFrame)) return;

	C_Position* cPos = entities->GetComponent<C_Position>(entity, Component::Position);
	sf::Vector3f pos = (relative ? sf::Vector3f(0.0f, 0.0f, 0.0f) :
		MakeSoundPosition(cPos->GetPosition(), cPos->GetElevation()));

	if (useId) {
		cSnd->SetSoundID(m_soundManager->Play(cSnd->GetSound(sound), pos));
	}
	else {
		m_soundManager->Play(cSnd->GetSound(sound), pos, false, relative);
	}
}