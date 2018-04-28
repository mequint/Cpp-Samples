#include "State.h"

StateManager * State::GetStateManager()
{
	return m_pStateManager;
}

void State::SetTransparent(bool transparent)
{
	m_transparent = transparent;
}

bool State::IsTransparent() const
{
	return m_transparent;
}

void State::SetTranscendent(bool transcendent)
{
	m_transcendent = transcendent;
}

bool State::IsTranscendent() const
{
	return m_transcendent;
}
