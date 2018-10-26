#include "State_Game.h"

#include "BlockHelper.h"
#include "StateManager.h"

// TODO: Make the block size configurable
State_Game::State_Game(StateManager* stateManager) : BaseState(stateManager),
	m_randomGenerator((int)ShapeType::Z)
{
	m_blockSize = 16.0f;
	m_grid = Grid(10, 22, 320, 128, 16);

	m_currentFallTime = 0.0f;
	m_nextFallTime = 1.0f;

	m_lines = 0;
	m_score = 0;
	m_speedUp = 10;
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
	eventManager->AddCallback(StateType::Game, "Key_W", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_A", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_S", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_D", &State_Game::MoveLander, this);

	eventManager->AddCallback(StateType::Game, "Key_Z", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_X", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_C", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Space", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Comma", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Period", &State_Game::MoveLander, this);
	eventManager->AddCallback(StateType::Game, "Key_Slash", &State_Game::MoveLander, this);

	m_font.loadFromFile("arial.ttf");

	std::string text = "Hold";
	m_holdBox = ShapeBox(m_font, 16, sf::Vector2f(220, 160), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), text);

	text = "Next";
	m_nextBox = ShapeBox(m_font, 16, sf::Vector2f(500, 160), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), text);

	m_linesBox = Label(m_font, 16);
	m_linesBox.SetPosition(sf::Vector2f(375, 128)); 

	text = "Level";
	m_levelBox = TitledTextBox(m_font, sf::Vector2f(220, 400), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), 24, text, 16);

	text = "Score";
	m_scoreBox = TitledTextBox(m_font, sf::Vector2f(500, 400), sf::Vector2f(m_blockSize * 5.0f, m_blockSize * 5.0f), 18, text, 16);

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
}

void State_Game::Destroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_P");

	eventManager->RemoveCallback(StateType::Game, "Key_Left");
	eventManager->RemoveCallback(StateType::Game, "Key_Right");
	eventManager->RemoveCallback(StateType::Game, "Key_Up");
	eventManager->RemoveCallback(StateType::Game, "Key_Down");
	eventManager->RemoveCallback(StateType::Game, "Key_W");
	eventManager->RemoveCallback(StateType::Game, "Key_A");
	eventManager->RemoveCallback(StateType::Game, "Key_S");
	eventManager->RemoveCallback(StateType::Game, "Key_D");

	eventManager->RemoveCallback(StateType::Game, "Key_Z");
	eventManager->RemoveCallback(StateType::Game, "Key_X");
	eventManager->RemoveCallback(StateType::Game, "Key_C");
	eventManager->RemoveCallback(StateType::Game, "Key_Space");
	eventManager->RemoveCallback(StateType::Game, "Key_Comma");
	eventManager->RemoveCallback(StateType::Game, "Key_Period");
	eventManager->RemoveCallback(StateType::Game, "Key_Slash");
}

void State_Game::Activate()
{
}

void State_Game::Deactivate()
{
}

void State_Game::Update(const sf::Time & time)
{
	// This will replace the current movement...might want to consider collecting moves...
	m_currentFallTime += time.asSeconds();
	if (m_currentFallTime >= m_nextFallTime)
	{
		m_currentFallTime = 0.0f;
		m_lander.SetMovement(Movement::Down);
	}

	m_grid.Update(m_lander, time.asSeconds());

	if (m_lander.HasLanded())
	{
		// Add lander blocks to the block pile
		sf::Vector2i landerPos = m_lander.GetCellPosition();
		for (auto block : m_lander.GetBlocks())
		{
			int col = block.x + landerPos.x;
			int row = block.y + landerPos.y;
			int type = static_cast<int>(m_lander.GetType());

			m_grid.AddBlock(col, row, type);
		}

		// Remove the lines
		int linesRemoved = m_grid.RemoveCompleteLines();
		m_lines += linesRemoved;

		// Update the fall time
		if (m_lines > m_speedUp)
		{
			m_nextFallTime -= 0.09f;

			m_speedUp += 10;

			if (m_nextFallTime < 0.05f)
			{
				m_nextFallTime = 0.05f;
			}
		}

		// Update score
		m_score += (400 * linesRemoved * linesRemoved);

		// Move next lander to playing field
		m_lander = m_next;
		m_lander.SetReferencePoint(m_grid.GetPosition());
		m_lander.SetCellPosition(m_lander.GetSpawnPoint().x, m_lander.GetSpawnPoint().y);
		m_lander.SetOnField(true);

		// Create a new next lander
		m_next = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_blockSize);
		m_nextBox.SetShape(&m_next);
		m_next.SetOnField(false);
	}

	// Update lander
	m_lander.Update(time.asSeconds());
	
	m_shadow = m_grid.GetShadow(m_lander);

	// Update UI elements
	m_linesBox.SetText("Lines - " + std::to_string(m_lines));
	m_levelBox.SetText(std::to_string(m_lines / 10));
	m_scoreBox.SetText(std::to_string(m_score));
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
}

void State_Game::Pause(EventDetails * details)
{
	m_stateManager->ChangeState(StateType::Paused);
}

void State_Game::MoveLander(EventDetails * details)
{
	std::string detail = details->m_name;
	if (detail == "Key_Down" || detail == "Key_S")
	{
		m_lander.SetMovement(Movement::Down);
	}
	else if (detail == "Key_Up" || detail == "Key_W" || detail == "Key_Space")
	{
		m_grid.SlamShape(m_lander);
	}
	else if (detail == "Key_Left" || detail == "Key_A")
	{
		m_lander.SetMovement(Movement::Left);
	}
	else if (detail == "Key_Right" || detail == "Key_D")
	{
		m_lander.SetMovement(Movement::Right);
	}
	else if (detail == "Key_Comma" || detail == "Key_Z")
	{
		m_lander.SetMovement(Movement::CCW);
	}
	else if (detail == "Key_Period" || detail == "Key_X")
	{
		m_lander.SetMovement(Movement::CW);
	}
	else if (detail == "Key_Slash" || detail == "Key_C")
	{
		SwapLanderWithHold();
	}
}

void State_Game::SwapLanderWithHold()
{
	if (m_hold.GetType() == ShapeType::None)
	{
		m_hold = m_lander;
		m_hold.SetCellPosition(0, 0);
		m_hold.SetOnField(false);
		m_hold.SetRotationIndex(0);
		m_holdBox.SetShape(&m_hold);

		m_lander = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_blockSize);
		m_lander.SetReferencePoint(m_grid.GetPosition());
		m_lander.SetCellPosition(m_lander.GetSpawnPoint().x, m_lander.GetSpawnPoint().y);
		m_lander.SetOnField(true);
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
}