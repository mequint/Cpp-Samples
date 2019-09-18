#pragma once

#include "qe/ECS/Core/Comp_Base.h"

enum class EntityState { Idle, Moving };

class Comp_State : public qe::Comp_Base
{
	public:
		Comp_State() : Comp_Base(Component::State) {}
		~Comp_State() {}

		void SetState(const EntityState& state) { m_state = state; }
		EntityState GetState() const { return m_state;  }

	private:
		EntityState m_state;
};