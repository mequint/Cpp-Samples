#pragma once

#include "BaseState.h"
#include "EventManager.h"
#include "Label.h"

class State_GameOver : public BaseState
{
	public:
		State_GameOver(StateManager* stateManager);
		~State_GameOver();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();

		void ReturnToTitle(EventDetails* details);

	private:
		Label m_result;

		Label m_finalScore;
		Label m_finalLevel;

		Label m_singles;
		Label m_doubles;
		Label m_triples;
		Label m_quadruples;
		Label m_lineTotal;

		Label m_combos;
		Label m_longestCombo;

		Label m_shapes;
		Label m_i;
		Label m_j;
		Label m_l;
		Label m_o;
		Label m_s;
		Label m_t;
		Label m_z;

		Label m_returnMessage;
};