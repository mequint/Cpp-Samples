#include "Game.h"

#include "ECS/ECS_Types.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"

#include "States/States.h"
#include "States/StateTypes.h"

Game::Game() :
	m_window("Pac Man", sf::Vector2u(800, 600)),
	m_stateManager(&m_context),
	m_entityManager(&m_systemManager) {

	m_elapsedTime = m_clock.restart();

	// Setup context
	m_context.m_entityManager = &m_entityManager;
	m_context.m_eventManager = m_window.getEventManager();
	m_context.m_fontManager = &m_fontManager;
	m_context.m_stateManager = &m_stateManager;
	m_context.m_systemManager = &m_systemManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_window = &m_window;

	// Register State Observers
	m_stateManager.registerObserver(m_context.m_eventManager);

	// Setup bindings
	m_window.getEventManager()->addBinding("Window_Close", static_cast<int>(qe::EventType::Closed), 0);

	m_window.getEventManager()->addBinding("KeyDown_W", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::W));
	m_window.getEventManager()->addBinding("KeyDown_A", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::A));
	m_window.getEventManager()->addBinding("KeyDown_S", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::S));
	m_window.getEventManager()->addBinding("KeyDown_D", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::D));
	m_window.getEventManager()->addBinding("KeyDown_P", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::P));
	m_window.getEventManager()->addBinding("KeyDown_Escape", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Escape));
	m_window.getEventManager()->addBinding("KeyDown_Enter", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Return));
	m_window.getEventManager()->addBinding("KeyDown_Up", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Up));
	m_window.getEventManager()->addBinding("KeyDown_Left", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Left));
	m_window.getEventManager()->addBinding("KeyDown_Down", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Down));
	m_window.getEventManager()->addBinding("KeyDown_Right", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Right));

	// Load Textures
	m_textureManager.loadResource("PacMan", "../media/Textures/PacMan.png");
	m_textureManager.loadResource("GameMap", "../media/Textures/PacManTiles.png");

	// Load Fonts
	m_fontManager.loadResource("Game", "../media/Fonts/Vegur-Regular.otf");

	// Setup ECS
	m_systemManager.setEntityManager(&m_entityManager);

	m_entityManager.registerComponent<C_Position>(static_cast<qe::ComponentType>(Component::Position));
	m_entityManager.registerComponent<C_Sprite>(static_cast<qe::ComponentType>(Component::Sprite));

	m_systemManager.registerSystem<S_Renderer>(static_cast<qe::SystemType>(System::Renderer));

	// Setup States
	m_stateManager.registerState<State_MainMenu>(static_cast<qe::StateType>(StateType::MainMenu));
	m_stateManager.registerState<State_Game>(static_cast<qe::StateType>(StateType::Game));

	// Change to first state
	m_stateManager.changeState(static_cast<qe::StateType>(StateType::MainMenu));
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