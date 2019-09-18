#pragma once

#include "qe/State/BaseState.h"
#include "qe/Event/EventManager.h"

#include "Views/ProgressBarView.h"

class State_Game : public qe::BaseState
{
	public:
		State_Game(qe::StateManager* stateManager);
		~State_Game();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();

		void Pause(qe::EventDetails* details);
		void MovePlayer(qe::EventDetails* details);
		void StopPlayer(qe::EventDetails* details);

	private:
		void CreateEntities();
		void SetupViews();

		ProgressBarView m_leftHealthView;
		ProgressBarView m_rightHealthView;

		int m_playerId;
};