#include "Game.h"

#include "States/State_Game.h"
#include "States/State_MainMenu.h"

Game::Game() :
	m_window("Pac Man", sf::Vector2u(800, 600)),
	m_stateManager(&m_context) {

	m_elapsedTime = m_clock.restart();

	// Setup context
	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.getEventManager();
	m_context.m_stateManager = &m_stateManager;

	// Register State Observers
	m_stateManager.registerObserver(m_context.m_eventManager);

	// Add bindings
	m_window.getEventManager()->addBinding("KeyDown_W", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::W));
	m_window.getEventManager()->addBinding("KeyDown_A", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::A));
	m_window.getEventManager()->addBinding("KeyDown_S", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::S));
	m_window.getEventManager()->addBinding("KeyDown_D", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::D));
	m_window.getEventManager()->addBinding("KeyDown_P", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::P));
	m_window.getEventManager()->addBinding("KeyDown_Escape", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Escape));

	m_window.getEventManager()->addBinding("KeyDown_Up", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Up));
	m_window.getEventManager()->addBinding("KeyDown_Left", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Left));
	m_window.getEventManager()->addBinding("KeyDown_Down", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Down));
	m_window.getEventManager()->addBinding("KeyDown_Right", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Right));

	// Setup States
	m_stateManager.registerState<State_MainMenu>(qe::StateType::MainMenu);
	//m_stateManager.registerState<State_PreGame>(qe::StateType::PreGame);
	m_stateManager.registerState<State_Game>(qe::StateType::Game);
	//m_stateManager.registerState<State_PostGame>(qe::StateType::PostGame);
	//m_stateManager.registerState<State_GameOver>(qe::StateType::GameOver);
	//m_stateManager.registerState<State_Pause>(qe::StateType::Pause);
	//m_stateManager.registerState<State_Credit>(qe::StateType::Credits);
	//m_stateManager.registerState<State_Intermission>(qe::StateType::Intermission);
	//m_stateManager.registerState<State_Splash>(qe::StateType::Intro);

	// Change to first state
	m_stateManager.changeState(qe::StateType::MainMenu);
}

void Game::update() {
	m_window.update();
	m_stateManager.update(m_elapsedTime);
}

void Game::draw() {
	m_window.beginDraw();
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::postProcess() {
	m_stateManager.removeDeadStates();
	m_elapsedTime = m_clock.restart();
}

qe::Window * Game::getWindow() {
	return &m_window;
}