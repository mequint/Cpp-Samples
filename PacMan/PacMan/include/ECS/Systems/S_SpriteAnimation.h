#pragma once

#include "qe/ECS/S_Base.h"

class S_SpriteAnimation : public qe::S_Base {
public:
	S_SpriteAnimation(qe::SystemManager* systemManager);
	~S_SpriteAnimation();

	// Inherited via S_Base
	void notify(const qe::Message& message);
	void update(float dt);
	void handleEvent(const qe::EntityId& entity, const qe::EntityEventType& event);

private:
	void changeAnimation(const qe::EntityId& entity, const std::string& anim, bool play);
};