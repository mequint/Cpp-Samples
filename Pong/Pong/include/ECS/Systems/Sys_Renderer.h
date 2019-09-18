#pragma once

#include "qe\ECS\Core\Sys_Base.h"
#include "qe\Window\Window.h"

class Comp_Drawable;

class Sys_Renderer : public qe::Sys_Base {
public:
	Sys_Renderer(qe::SystemManager* systemManager);
	~Sys_Renderer();

	void Update(float dt);
	void HandleEvent(const qe::EntityId& entity, const qe::EntityEvent& event);

	void Notify(const qe::Message& message);
	void Render(qe::Window* window, unsigned int layer);

private:
	Comp_Drawable * GetDrawableFromType(const qe::EntityId& entityId);

	qe::Bitmask m_drawableTypes;
};