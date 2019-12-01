#pragma once

#include "C_Base.h"

enum class EntityState { Idle, Walking, Attacking, Hurt, Dying };

class C_State : public C_Base {
public:
	C_State() : C_Base(Component::State) {}

	void ReadIn(std::stringstream& stream) {
		unsigned int state = 0;
		stream >> state;

		m_state = static_cast<EntityState>(state);
	}

	EntityState GetState() { return m_state; }
	void SetState(const EntityState& state) {
		m_state = state;
	}

private:
	EntityState m_state;
};