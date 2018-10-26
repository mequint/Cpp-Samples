#include "Game.h"

#include "State_Game.h"

Game::Game() : m_window("Tetrominos", sf::Vector2u(800, 600)), m_stateManager(&m_context)
{
	// Start the clock
	m_clock.restart();

	// Setup context
	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();

	// Setup bindings
	SetupBindings();

	m_stateManager.ChangeState(StateType::Game);
}

void Game::SetupBindings()
{
	m_window.GetEventManager()->AddBinding("CloseWindow", (int)EventType::Closed, 0);
	m_window.GetEventManager()->AddBinding("Key_Escape", (int)EventType::KeyDown, (int)sf::Keyboard::Escape);
	m_window.GetEventManager()->AddBinding("Key_P", (int)EventType::KeyDown, (int)sf::Keyboard::P);

	m_window.GetEventManager()->AddBinding("Key_Up", (int)EventType::KeyDown, (int)sf::Keyboard::Up);
	m_window.GetEventManager()->AddBinding("Key_Left", (int)EventType::KeyDown, (int)sf::Keyboard::Left);
	m_window.GetEventManager()->AddBinding("Key_Right", (int)EventType::KeyDown, (int)sf::Keyboard::Right);
	m_window.GetEventManager()->AddBinding("Key_Down", (int)EventType::KeyDown, (int)sf::Keyboard::Down);
	m_window.GetEventManager()->AddBinding("Key_Comma", (int)EventType::KeyDown, (int)sf::Keyboard::Comma);
	m_window.GetEventManager()->AddBinding("Key_Period", (int)EventType::KeyDown, (int)sf::Keyboard::Period);
	m_window.GetEventManager()->AddBinding("Key_Slash", (int)EventType::KeyDown, (int)sf::Keyboard::Slash);
	m_window.GetEventManager()->AddBinding("Key_Space", (int)EventType::KeyDown, (int)sf::Keyboard::Space);

	m_window.GetEventManager()->AddBinding("Key_W", (int)EventType::KeyDown, (int)sf::Keyboard::W);
	m_window.GetEventManager()->AddBinding("Key_A", (int)EventType::KeyDown, (int)sf::Keyboard::A);
	m_window.GetEventManager()->AddBinding("Key_D", (int)EventType::KeyDown, (int)sf::Keyboard::D);
	m_window.GetEventManager()->AddBinding("Key_S", (int)EventType::KeyDown, (int)sf::Keyboard::S);
	m_window.GetEventManager()->AddBinding("Key_Z", (int)EventType::KeyDown, (int)sf::Keyboard::Z);
	m_window.GetEventManager()->AddBinding("Key_X", (int)EventType::KeyDown, (int)sf::Keyboard::X);
	m_window.GetEventManager()->AddBinding("Key_C", (int)EventType::KeyDown, (int)sf::Keyboard::C);
}

Game::~Game() {}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_elapsedTime);
}

void Game::Draw()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::PostProcess()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

sf::Time Game::GetElapsedtime()
{
	return m_clock.getElapsedTime();
}

Window* Game::GetWindow()
{
	return &m_window;
}

/**************************************** Helper methods ****************************************/

void Game::RestartClock()
{
	m_elapsedTime = m_clock.restart();
}