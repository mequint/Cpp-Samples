#pragma once

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

enum class EntityState { Idle, Moving };

class C_State : public qe::C_Base {
public:
	C_State() : qe::C_Base(static_cast<qe::ComponentType>(Component::State)) {}
	~C_State() = default;

	void setState(const EntityState& state) { m_state = state; }
	EntityState getState() const { return m_state; }

private:
	EntityState m_state;
};