#pragma once

#include "qe/ECS/S_Base.h"
#include "qe/Window/Window.h"

class S_Renderer : public qe::S_Base {
public:
	S_Renderer(qe::SystemManager* systemManager);
	~S_Renderer();

	// Inherited via S_Base
	void notify(const qe::Message & message);
	void update(float dt);
	void handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event);

	void render(qe::Window* window);

private:
};