#include "State_Game.h"

#include "StateManager.h"

// TODO: Make the block size configurable
State_Game::State_Game(StateManager* stateManager) : BaseState(stateManager),
	m_randomGenerator((int)ShapeType::Z)
{
	m_blockSize = 16;
	m_grid = Grid(10, 20, 320, 160, 16);

	m_spawnX = 5;
	m_spawnY = 2;

	m_currentFallTime = 0.0f;
	m_nextFallTime = 1.0f;

	m_lines = 0;
	m_speedUp = 10;
}

State_Game::~State_Game()
{
}

void State_Game::Create()
{
	m_font.loadFromFile("arial.ttf");

	std::string text = "Hold";
	m_holdBox = ShapeBox(m_font, text, 16);
	m_holdBox.SetPosition(sf::Vector2f(220, 160));
	m_holdBox.SetRectangle(80, 80);

	text = "Next";
	m_nextBox = ShapeBox(m_font, text, 16);	
	m_nextBox.SetPosition(sf::Vector2f(500, 160));
	m_nextBox.SetRectangle(80, 80);

	m_linesBox = TextBox(m_font, 16);
	m_linesBox.SetPosition(sf::Vector2f(375, 130)); 

	m_lander = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_grid.GetPosition());
	m_lander.SetCellPosition(m_spawnX, m_spawnY);

	//m_next = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_nextBox.GetPosition());
}

void State_Game::Destroy()
{
}

void State_Game::Activate()
{
}

void State_Game::Deactivate()
{
}

void State_Game::HandleEvents()
{
	auto window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_stateManager->GetContext()->m_window->Close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_lander.SetMovement(Movement::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_lander.SetMovement(Movement::Right);
		}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		//{
		//	m_lander.SetMovement(Movement::Up);
		//}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_lander.SetMovement(Movement::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
		{
			m_lander.SetMovement(Movement::CCW);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
		{
			m_lander.SetMovement(Movement::CW);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_stateManager->GetContext()->m_window->Close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			m_grid.ToggleVisibility();
		}
	}
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

	m_grid.CheckCollisions(m_lander);

	if (m_lander.HasLanded())
	{
		sf::Vector2i landerPos = m_lander.GetCellPosition();
		for (auto block : m_lander.GetBlocks())
		{
			int col = block.x + landerPos.x;
			int row = block.y + landerPos.y;
			int type = static_cast<int>(m_lander.GetType());

			m_grid.AddBlock(col, row, type);
		}

		int score = m_grid.RemoveCompleteLines();
		m_lines += score;

		if (m_lines > m_speedUp)
		{
			// TODO: Fine tune this one
			m_nextFallTime -= 0.1f;

			m_speedUp += 10;
		}

		m_lander = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_grid.GetPosition());
		m_lander.SetCellPosition(m_spawnX, m_spawnY);

		//m_lander = m_next;
		//m_lander.SetCellPosition(m_spawnX, m_spawnY);

		//m_next = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_nextBox.GetPosition());
		//m_nextBox.SetShape(&m_next);
	}

	m_lander.Update(time.asSeconds());

	m_linesBox.SetText("Lines - " + std::to_string(m_lines));
}

void State_Game::Draw()
{
	auto renderWindow = m_stateManager->GetContext()->m_window->GetRenderWindow();

	m_linesBox.Draw(*renderWindow);
	m_holdBox.Draw(*renderWindow);
	m_nextBox.Draw(*renderWindow);
	m_grid.Draw(*renderWindow);
	m_lander.Draw(*renderWindow);
}
