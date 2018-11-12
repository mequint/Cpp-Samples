#pragma once

#include <SFML/Audio.hpp>

#include "BaseState.h"

#include "EventManager.h"
#include "GameData.h"
#include "Grid.h"
#include "Label.h"
#include "MessageAnimator.h"
#include "RandomGenerator.h"
#include "Shape.h"
#include "ShapeBox.h"
#include "TitledTextBox.h"

class State_Game : public BaseState
{
	public:
		State_Game(StateManager* stateManager);
		~State_Game();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void UpdateUIPieces();
		void UpdateFallTime();
		void Draw();

		void Pause(EventDetails* details);
		void MoveLander(EventDetails* details);

		void Reset();

	private:

		void CheckForGameOver();
		void MoveNextLanderToGrid();
		void SwapLanderWithHold();

		void LoadSounds();

		std::string GetLineRemovalMessage(int linesRemoved);
		void UpdateGameStats(int linesRemoved);

		RandomGenerator m_randomGenerator;
		bool m_holdActivated;

		// User Interface
		Label m_linesBox;
		MessageAnimator m_messageAnimator;

		ShapeBox m_holdBox;
		ShapeBox m_nextBox;
		TitledTextBox m_levelBox;
		TitledTextBox m_scoreBox;

		// Sound Effects
		sf::SoundBuffer m_blockLandBuffer;
		sf::Sound m_blockLand;
		sf::SoundBuffer m_blockRotateBuffer;
		sf::Sound m_blockRotate;
		sf::SoundBuffer m_removeLinesBuffer;
		sf::Sound m_removeLines;

		// Game variables
		GameData* m_gameData;
		float m_blockSize;

		// Game Objects
		Grid m_grid;
		Shape m_lander;
		Shape m_next;
		Shape m_hold;
		Shape m_shadow;

		float m_currentFallTime;
		float m_nextFallTime;
		int m_linesToNextLevel;

		bool m_currentComboCount;
		bool m_lastBlockRemovedLines;
		int m_lastLinesRemoved;

		// In Game States
		bool m_gamePlaying;
};