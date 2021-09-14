#include "Game.h"

#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"

#include "States/States.h"
#include "States/StateTypes.h"

Game::Game() :
	m_window("Pac Man", sf::Vector2u(800, 600)),
	m_stateManager(&m_context),
	m_systemManager(&m_fontManager, &m_textureManager, &m_window),
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
	m_textureManager.loadResource("Pill", "../media/Textures/Pill.png");
	m_textureManager.loadResource("Pellet", "../media/Textures/Pellet.png");

	// Load Fonts
	m_fontManager.loadResource("Game", "../media/Fonts/Vegur-Regular.otf");

	// Setup ECS
	m_systemManager.setEntityManager(&m_entityManager);

	m_entityManager.registerComponent<C_Collider>(static_cast<qe::ComponentType>(Component::Collider));
	m_entityManager.registerComponent<C_Controller>(static_cast<qe::ComponentType>(Component::Controller));
	m_entityManager.registerComponent<C_Consumable>(static_cast<qe::ComponentType>(Component::Consumable));
	m_entityManager.registerComponent<C_EntityType>(static_cast<qe::ComponentType>(Component::EntityType));
	m_entityManager.registerComponent<C_Motion>(static_cast<qe::ComponentType>(Component::Motion));
	m_entityManager.registerComponent<C_Points>(static_cast<qe::ComponentType>(Component::Points));
	m_entityManager.registerComponent<C_Position>(static_cast<qe::ComponentType>(Component::Position));
	m_entityManager.registerComponent<C_Score>(static_cast<qe::ComponentType>(Component::Score));
	m_entityManager.registerComponent<C_Sprite>(static_cast<qe::ComponentType>(Component::Sprite));
	m_entityManager.registerComponent<C_State>(static_cast<qe::ComponentType>(Component::State));

	m_systemManager.registerSystem<S_AppState>(static_cast<qe::SystemType>(System::AppState));
	m_systemManager.registerSystem<S_Collision>(static_cast<qe::SystemType>(System::Collision));
	m_systemManager.registerSystem<S_Consumption>(static_cast<qe::SystemType>(System::Consumption));
	m_systemManager.registerSystem<S_Control>(static_cast<qe::SystemType>(System::Control));
	m_systemManager.registerSystem<S_GameUI>(static_cast<qe::SystemType>(System::GameUI));
	m_systemManager.registerSystem<S_Movement>(static_cast<qe::SystemType>(System::Movement));
	m_systemManager.registerSystem<S_Renderer>(static_cast<qe::SystemType>(System::Renderer));
	m_systemManager.registerSystem<S_Scoring>(static_cast<qe::SystemType>(System::Scoring));
	m_systemManager.registerSystem<S_State>(static_cast<qe::SystemType>(System::State));

	m_systemManager.getSystem<S_AppState>(static_cast<qe::SystemType>(System::AppState))->setStateManager(&m_stateManager);

	// Setup States
	m_stateManager.registerState<State_MainMenu>(StateType::MainMenu);
	m_stateManager.registerState<State_Game>(StateType::Game);
	m_stateManager.registerState<State_Paused>(StateType::Paused);

	// Change to first state
	m_stateManager.changeState(StateType::MainMenu);
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