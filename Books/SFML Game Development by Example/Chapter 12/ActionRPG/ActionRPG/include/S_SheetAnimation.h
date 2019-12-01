#pragma once

#include "S_Base.h"

class S_SheetAnimation : public S_Base {
public:
	S_SheetAnimation(SystemManager* systemManager);
	~S_SheetAnimation();

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);

private:
	void ChangeAnimation(const EntityId& entity, const std::string& anim, bool play, bool loop);
};