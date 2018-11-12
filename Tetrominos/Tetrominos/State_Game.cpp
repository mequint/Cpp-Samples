#include "State_Game.h"

#include "BlockHelper.h"
#include "StateManager.h"

#include <iostream>

// TODO: Make the block size configurable
State_Game::State_Game(StateManager* stateManager) : BaseState(stateManager), m_randomGenerator((int)ShapeType::Z),
	m_grid(10, 22, 320, 128, 16), m_messageAnimator(800, 600), m_lastLinesRemoved(0), m_currentComboCount(0), m_lastBlockRemovedLines(false)
{
	m_blockSize = 16.0f;
	m_gameData = m_stateManager->GetContext()->m_gameData;
}

State_Game::~State_Game()
{
}

void State_Game::Create()
{
	auto* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);

	eventManager->AddCallback(StateType::Game, "Key_Left", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Right", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Up", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Down", &State_Game::MoveLander, this);

	eventManager->AddCallback(StateType::Game, "Key_Z", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_X", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_C", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Space", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Slash", &State_Game::MoveLander, this);

	eventManager->AddCallback(StateType::Game, "Button_X", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_A", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_B", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_L1", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_R1", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_L2", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_R2", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Button_Start", &State_Game::Pause, this);
	eventManager->AddCallback(StateType::Game, "Joystick_Moved", &State_Game::MoveLander, this);

	sf::Font* font = m_stateManager->GetContext()->m_fontManager->GetFont("Game");

	std::string text = "Hold";
	m_holdBox = ShapeBox(*font, 16, sf::Vector2f(220, 160), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), text);

	text = "Next";
	m_nextBox = ShapeBox(*font, 16, sf::Vector2f(500, 160), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), text);

	m_linesBox = Label(*font, 16);
	m_linesBox.SetPosition(sf::Vector2f(375, 128)); 

	text = "Level";
	m_levelBox = TitledTextBox(*font, sf::Vector2f(220, 400), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), 24, text, 16);

	text = "Score";
	m_scoreBox = TitledTextBox(*font, sf::Vector2f(500, 400), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), 18, text, 16);

	LoadSounds();

	Reset();
}

void State_Game::Destroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_P");

	eventManager->RemoveCallback(StateType::Game, "Key_Left");
	eventManager->RemoveCallback(StateType::Game, "Key_Right");
	eventManager->RemoveCallback(StateType::Game, "Key_Up");
	eventManager->RemoveCallback(StateType::Game, "Key_Down");

	eventManager->RemoveCallback(StateType::Game, "Key_Z");
	eventManager->RemoveCallback(StateType::Game, "Key_X");
	eventManager->RemoveCallback(StateType::Game, "Key_C");
	eventManager->RemoveCallback(StateType::Game, "Key_Space");;
	eventManager->RemoveCallback(StateType::Game, "Key_Slash");

	eventManager->RemoveCallback(StateType::Game, "Button_X");
	eventManager->RemoveCallback(StateType::Game, "Button_A");
	eventManager->RemoveCallback(StateType::Game, "Button_B");
	eventManager->RemoveCallback(StateType::Game, "Button_L1");
	eventManager->RemoveCallback(StateType::Game, "Button_R1");
	eventManager->RemoveCallback(StateType::Game, "Button_L2");
	eventManager->RemoveCallback(StateType::Game, "Button_R2");
	eventManager->RemoveCallback(StateType::Game, "Button_Start");
}

void State_Game::Activate()
{
	if (m_gameData->NewGame)
	{
		Reset();
	}
}

void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time & time)
{
	float elapsedTime = time.asSeconds();

	m_currentFallTime += elapsedTime;

	if (m_gamePlaying)
	{
		if (m_currentFallTime >= m_nextFallTime)
		{
			m_currentFallTime = 0.0f;
			m_lander.SetMovement(Movement::Down);
		}

		m_grid.CheckCollisions(m_lander);
		m_grid.Update(m_lander, elapsedTime);

		if (m_lander.HasLanded())
		{
			// Remove the lines
			int linesRemoved = m_grid.GetLinesRemoved();

			// Play sounds...
			if (linesRemoved > 0)
			{
				std::string message = GetLineRemovalMessage(linesRemoved);

				m_messageAnimator.AddMessage(message);
				m_messageAnimator.Start();

				m_removeLines.play();

				if (m_lastLinesRemoved)
				{
					message = "Combo";
					m_messageAnimator.AddMessage(message);

					m_lastBlockRemovedLines = true;
					m_currentComboCount++;
				}

				m_lastLinesRemoved = linesRemoved;
			}
			else
			{
				m_lastBlockRemovedLines = false;
				m_currentComboCount = 0;
				m_lastLinesRemoved = 0;
				m_blockLand.play();
			}

			UpdateGameStats(linesRemoved);
			UpdateFallTime();			
			m_lander = Shape(ShapeType::None, m_blockSize);
		}

		if (m_grid.ReadyNextShape())
		{
			MoveNextLanderToGrid();

			CheckForGameOver();

			m_holdActivated = false;
		}

		// Update lander
		m_lander.Update(elapsedTime);

		// Message animator update
		m_messageAnimator.Update(elapsedTime);

		UpdateUIPieces();
	}
	else
	{
 		m_messageAnimator.Update(elapsedTime);

		if (m_messageAnimator.IsAnimationComplete())
		{
			m_stateManager->ChangeState(StateType::GameOver);
		}
	}
}

void State_Game::CheckForGameOver()
{
	for (auto block : m_lander.GetBlocks())
	{
		if (m_grid.HasBlock(m_lander.GetCellPosition().x + block.x, m_lander.GetCellPosition().y + block.y))
		{
			m_gamePlaying = false;

			std::string message = "GAME OVER";
			m_messageAnimator.AddMessage(message);
			m_messageAnimator.Start();

			return;
		}
	}
}

void State_Game::MoveNextLanderToGrid()
{
	// Move next lander to playing field
	m_lander = m_next;
	m_lander.SetReferencePoint(m_grid.GetPosition());
	m_lander.SetCellPosition(m_lander.GetSpawnPoint().x, m_lander.GetSpawnPoint().y);
	m_lander.SetOnField(true);

	// Create a new next lander 
	int nextInt = m_randomGenerator.GetNextInt();
	m_next = Shape(ShapeType(nextInt), m_blockSize);
	m_nextBox.SetShape(&m_next);
	m_next.SetOnField(false);

	// Add shape count to the game stats
	++(m_stateManager->GetContext()->m_gameData->ShapeCount[nextInt]);
}

void State_Game::UpdateUIPieces()
{
	m_shadow = m_grid.CastShadow(m_lander);
	m_linesBox.SetText("Lines - " + std::to_string(m_gameData->Lines));
	m_levelBox.SetText(std::to_string(m_gameData->Level));
	m_scoreBox.SetText(std::to_string(m_gameData->Score));
}

void State_Game::UpdateFallTime()
{
	if (m_gameData->Lines >= m_linesToNextLevel)
	{
		m_nextFallTime -= 0.09f;

		m_linesToNextLevel += 10;

		if (m_nextFallTime < 0.05f)
		{
			m_nextFallTime = 0.05f;
		}
	}
}

void State_Game::Draw()
{
	auto renderWindow = m_stateManager->GetContext()->m_window->GetRenderWindow();

	m_linesBox.Draw(*renderWindow);
	m_holdBox.Draw(*renderWindow);
	m_nextBox.Draw(*renderWindow);
	m_levelBox.Draw(*renderWindow);
	m_scoreBox.Draw(*renderWindow);
	m_grid.Draw(*renderWindow);
	m_lander.Draw(*renderWindow);
	m_shadow.Draw(*renderWindow);

	m_messageAnimator.Draw(*renderWindow);
}

void State_Game::Pause(EventDetails * details)
{
	// We don't want the game to reset if the game is returning from the puase state...
	m_gameData->NewGame = false;

	m_stateManager->ChangeState(StateType::Paused);
}

void State_Game::MoveLander(EventDetails* details)
{
	std::string detail = details->m_name;
	if (detail == "Key_Down")
	{
		m_lander.SetMovement(Movement::Down);
	}
	else if (detail == "Key_Up" || detail == "Key_Space")
	{
		m_grid.SlamShape(m_lander);
	}
	else if (detail == "Key_Left")
	{
		m_lander.SetMovement(Movement::Left);
	}
	else if (detail == "Key_Right")
	{
		m_lander.SetMovement(Movement::Right);
	}
	else if (detail == "Key_Z" || detail == "Button_A")
	{
		m_lander.SetMovement(Movement::CCW);
	}
	else if (detail == "Key_X" || detail == "Button_B")
	{
		m_lander.SetMovement(Movement::CW);
	}
	else if (detail == "Key_Slash" || detail == "Key_C" || 
		detail == "Button_X" || detail == "Button_L1" || detail == "Button_R1" || detail == "Button_L2" || detail == "Button_R2")
	{
		SwapLanderWithHold();
	}
	else if (detail == "Joystick_Moved")
	{
		float posX = details->m_joystickXY.x;
		float posY = details->m_joystickXY.y;

		if (posX == -100)
		{
			m_lander.SetMovement(Movement::Left);
		}
		else if (posX == 100)
		{
			m_lander.SetMovement(Movement::Right);
		}
		else if (posY == -100)
		{
			m_grid.SlamShape(m_lander);
		}
		else if (posY == 100)
		{
			m_lander.SetMovement(Movement::Down);
		}
	}
}

void State_Game::Reset()
{
	m_lander = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_blockSize);
	m_lander.SetReferencePoint(m_grid.GetPosition());
	m_lander.SetCellPosition(m_lander.GetSpawnPoint().x, m_lander.GetSpawnPoint().y);
	m_lander.SetOnField(true);

	m_next = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_blockSize);
	m_next.SetOnField(false);
	m_nextBox.SetShape(&m_next);

	m_hold = Shape(ShapeType::None, m_blockSize);
	m_next.SetOnField(false);
	m_holdBox.SetShape(&m_hold);

	m_currentFallTime = 0.0f;
	m_nextFallTime = 1.0f;

	m_linesToNextLevel = 10;

	m_holdActivated = false;

	m_grid.Reset();

	m_gameData->Clear();

	m_gamePlaying = true;
}

void State_Game::SwapLanderWithHold()
{
	if (m_holdActivated) return;

	if (m_hold.GetType() == ShapeType::None)
	{
		m_hold = m_lander;
		m_hold.SetCellPosition(0, 0);
		m_hold.SetOnField(false);
		m_hold.SetRotationIndex(0);
		m_holdBox.SetShape(&m_hold);

		MoveNextLanderToGrid();
	}
	else
	{
		auto temp = m_hold;
		m_hold = m_lander;
		m_lander = temp;
		
		m_hold.SetCellPosition(0, 0);
		m_hold.SetOnField(false);
		m_hold.SetRotationIndex(0);
		m_holdBox.SetShape(&m_hold);

		m_lander.SetReferencePoint(m_grid.GetPosition());
		m_lander.SetCellPosition(m_lander.GetSpawnPoint().x, m_lander.GetSpawnPoint().y);
		m_lander.SetOnField(true);
	}

	m_holdActivated = true;
}

void State_Game::LoadSounds()
{
	m_blockLandBuffer.loadFromFile("BlockLand.wav");
	m_blockLand.setBuffer(m_blockLandBuffer);
	m_blockLand.setVolume(100);

	m_blockRotateBuffer.loadFromFile("BlockRotate.wav");
	m_blockRotate.setBuffer(m_blockRotateBuffer);
	m_blockRotate.setVolume(100);

	m_removeLinesBuffer.loadFromFile("RemoveLines.wav");
	m_removeLines.setBuffer(m_removeLinesBuffer);
	m_removeLines.setVolume(100);
}

std::string State_Game::GetLineRemovalMessage(int linesRemoved)
{
	std::string message = "";

	switch (linesRemoved)
	{
		case 1:
			message = "Sweet";
			break;

		case 2:
			message = "Groovy";
			break;

		case 3:
			message = "Great!";
			break;

		case 4:
			message = "Awesome!!!";
			break;
	}

	return message;
}

void State_Game::UpdateGameStats(int linesRemoved)
{
	int score = (100 * linesRemoved * linesRemoved);
	int comboScore = score * m_currentComboCount;

	m_gameData->Score += score + comboScore;

	switch (linesRemoved)
	{
		case 1:
			++(m_gameData->Singles);
			break;

		case 2:
			++(m_gameData->Doubles);
			break;

		case 3:
			++(m_gameData->Triples);
			break;

		case 4:
			++(m_gameData->Quadruples);
			break;
	}

	m_gameData->Lines += linesRemoved;
	if (m_gameData->Lines >= m_linesToNextLevel)
	{
		++(m_gameData->Level);

		std::string message = "Level Up";
		m_messageAnimator.AddMessage(message);
	}

	if (m_lastBlockRemovedLines)
	{
		++(m_gameData->Combos);
		++(m_currentComboCount);

		if (m_currentComboCount > m_gameData->LongestCombo)
		{
			m_gameData->LongestCombo = m_currentComboCount;
		}
	}
}
