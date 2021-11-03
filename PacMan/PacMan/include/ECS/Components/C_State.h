#pragma once

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

enum class eEntityState { Dying, Idle, Moving, Scramble, Ambush, Chase, Fickle, Ignorant, Retreat, ReturnHome, Waiting };

class C_State : public qe::C_Base {
public:
	C_State() : qe::C_Base(static_cast<qe::ComponentType>(Component::State)) {}
	~C_State() = default;

	void setCurrentState(const eEntityState& state) { m_currentState = state; }
	eEntityState getCurrentState() const { return m_currentState; }

	void setInitialState(const eEntityState& state) { m_initialState = state; }
	eEntityState getInitialState() const { return m_initialState; }

private:
	eEntityState m_currentState;
	eEntityState m_initialState;
};