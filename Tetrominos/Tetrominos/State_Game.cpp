#include "State_Game.h"

#include "StateManager.h"

// TODO: Make the block size configurable
State_Game::State_Game(StateManager* stateManager) : BaseState(stateManager),
	m_randomGenerator((int)ShapeType::Z)
{
	m_blockSize = 16;
	m_grid = Grid(10, 20, 320, 160, 16);
	m_lander = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_grid);

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
			m_lander.SetDirection(Direction::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_lander.SetDirection(Direction::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_lander.SetDirection(Direction::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_lander.SetDirection(Direction::Down);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
		{
			m_lander.SetRotation(Rotation::CCW);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
		{
			m_lander.SetRotation(Rotation::CW);
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
	m_currentFallTime += time.asSeconds();
	if (m_currentFallTime >= m_nextFallTime)
	{
		m_currentFallTime = 0.0f;
		m_lander.SetDirection(Direction::Down);
	}

	if (m_lander.HasLanded())
	{
		sf::Vector2i landerPos = m_lander.GetPosition();
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

		m_lander = Shape(ShapeType(m_randomGenerator.GetNextInt()), m_grid);
		m_lander.SetPosition(m_spawnX, m_spawnY);
	}

	m_lander.Update(time.asSeconds());
}

void State_Game::Draw()
{
	auto renderWindow = m_stateManager->GetContext()->m_window->GetRenderWindow();
	m_grid.Draw(*renderWindow);
	m_lander.Draw(*renderWindow);
}
