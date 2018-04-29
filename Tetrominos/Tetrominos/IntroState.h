#pragma once

#include "State.h"

class Text;

class IntroState : public State
{
	public:
		IntroState(StateManager* stateManager);
		virtual ~IntroState();

		virtual void Initialize();
		virtual void Cleanup();

		virtual void Activate();
		virtual void Deactivate();

		virtual void Update(float dt);
		virtual void Draw();

	private:
		Text* m_text;
};