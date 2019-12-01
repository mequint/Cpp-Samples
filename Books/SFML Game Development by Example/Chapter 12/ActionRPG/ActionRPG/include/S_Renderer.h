#pragma once

#include "S_Base.h"
#include "Window.h"

class S_Renderer : public S_Base {
public:
	S_Renderer(SystemManager* systemManager);
	~S_Renderer();

	void Update(float dt);
	void HandleEvent(const EntityId& entity, const EntityEvent& event);
	void Notify(const Message& message);
	void Render(Window* window, unsigned int layer);

private:
	void SetSheetDirection(const EntityId& entity, const Direction& dir);
	void SortDrawables();
};