#include "Game.h"

#include "State_Game.h"

Game::Game() : m_window("Tetrominos", sf::Vector2u(800, 600)), m_stateManager(&m_context)
{
	// Start the clock
	m_clock.restart();

	// Setup context
	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_fontManager = &m_fontManager;

	// Setup bindings
	SetupBindings();

	// Load fonts
	m_fontManager.LoadFont("arial.ttf", "Game");

	m_stateManager.ChangeState(StateType::Title);
}

void Game::SetupBindings()
{
	m_window.GetEventManager()->AddBinding("CloseWindow", (int)EventType::Closed, 0);
	m_window.GetEventManager()->AddBinding("Key_Escape", (int)EventType::KeyDown, (int)sf::Keyboard::Escape);
	m_window.GetEventManager()->AddBinding("Key_Enter", (int)EventType::KeyDown, (int)sf::Keyboard::Return);
	m_window.GetEventManager()->AddBinding("Key_P", (int)EventType::KeyDown, (int)sf::Keyboard::P);

	m_window.GetEventManager()->AddBinding("Key_Up", (int)EventType::KeyDown, (int)sf::Keyboard::Up);
	m_window.GetEventManager()->AddBinding("Key_Left", (int)EventType::KeyDown, (int)sf::Keyboard::Left);
	m_window.GetEventManager()->AddBinding("Key_Right", (int)EventType::KeyDown, (int)sf::Keyboard::Right);
	m_window.GetEventManager()->AddBinding("Key_Down", (int)EventType::KeyDown, (int)sf::Keyboard::Down);
	m_window.GetEventManager()->AddBinding("Key_Slash", (int)EventType::KeyDown, (int)sf::Keyboard::Slash);
	m_window.GetEventManager()->AddBinding("Key_Space", (int)EventType::KeyDown, (int)sf::Keyboard::Space);

	m_window.GetEventManager()->AddBinding("Key_Z", (int)EventType::KeyDown, (int)sf::Keyboard::Z);
	m_window.GetEventManager()->AddBinding("Key_X", (int)EventType::KeyDown, (int)sf::Keyboard::X);
	m_window.GetEventManager()->AddBinding("Key_C", (int)EventType::KeyDown, (int)sf::Keyboard::C);

	m_window.GetEventManager()->AddBinding("Button_X", (int)EventType::JButtonDown, 0);
	m_window.GetEventManager()->AddBinding("Button_A", (int)EventType::JButtonDown, 1);
	m_window.GetEventManager()->AddBinding("Button_B", (int)EventType::JButtonDown, 2);
	m_window.GetEventManager()->AddBinding("Button_Y", (int)EventType::JButtonDown, 3);
	m_window.GetEventManager()->AddBinding("Button_L1", (int)EventType::JButtonDown, 4);
	m_window.GetEventManager()->AddBinding("Button_R1", (int)EventType::JButtonDown, 5);
	m_window.GetEventManager()->AddBinding("Button_L2", (int)EventType::JButtonDown, 6);
	m_window.GetEventManager()->AddBinding("Button_R2", (int)EventType::JButtonDown, 7);
	m_window.GetEventManager()->AddBinding("Button_Select", (int)EventType::JButtonDown, 8);
	m_window.GetEventManager()->AddBinding("Button_Start", (int)EventType::JButtonDown, 9);
	m_window.GetEventManager()->AddBinding("Button_L3", (int)EventType::JButtonDown, 10);
	m_window.GetEventManager()->AddBinding("Button_R3", (int)EventType::JButtonDown, 11);

	m_window.GetEventManager()->AddBinding("Joystick_Moved", (int)EventType::JoystickMoved, 0);
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