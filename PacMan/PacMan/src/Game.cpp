#include "Game.h"

#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"
#include "qe/Window/EventLoader.h"
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
	m_context.m_random = &m_random;
	m_context.m_stateManager = &m_stateManager;
	m_context.m_systemManager = &m_systemManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_window = &m_window;

	// Register State Observers
	m_stateManager.registerObserver(m_context.m_eventManager);

	// Setup bindings
	qe::EventLoader loader(m_window.getEventManager());
	loader.loadFromJsonFile("../media/eventBindings.json");

	// Load Textures
	m_textureManager.loadResourcesFromJson("../media/textures.json");

	// Load Fonts
	m_fontManager.loadResourcesFromJson("../media/fonts.json");

	// Setup ECS
	m_systemManager.setEntityManager(&m_entityManager);

	m_entityManager.registerComponent<C_AnimatedSprite>(static_cast<qe::ComponentType>(Component::AnimatedSprite));
	m_entityManager.registerComponent<C_Collider>(static_cast<qe::ComponentType>(Component::Collider));
	m_entityManager.registerComponent<C_Controller>(static_cast<qe::ComponentType>(Component::Controller));
	m_entityManager.registerComponent<C_Consumable>(static_cast<qe::ComponentType>(Component::Consumable));
	m_entityManager.registerComponent<C_EntityType>(static_cast<qe::ComponentType>(Component::EntityType));
	m_entityManager.registerComponent<C_GameAgent>(static_cast<qe::ComponentType>(Component::GameAgent));
	m_entityManager.registerComponent<C_Motion>(static_cast<qe::ComponentType>(Component::Motion));
	m_entityManager.registerComponent<C_Points>(static_cast<qe::ComponentType>(Component::Points));
	m_entityManager.registerComponent<C_Position>(static_cast<qe::ComponentType>(Component::Position));
	m_entityManager.registerComponent<C_Score>(static_cast<qe::ComponentType>(Component::Score));
	m_entityManager.registerComponent<C_Sprite>(static_cast<qe::ComponentType>(Component::Sprite));
	m_entityManager.registerComponent<C_State>(static_cast<qe::ComponentType>(Component::State));

	m_systemManager.registerSystem<S_AI>(static_cast<qe::SystemType>(System::AI));
	m_systemManager.registerSystem<S_AppState>(static_cast<qe::SystemType>(System::AppState));
	m_systemManager.registerSystem<S_Collision>(static_cast<qe::SystemType>(System::Collision));
	m_systemManager.registerSystem<S_Consumption>(static_cast<qe::SystemType>(System::Consumption));
	m_systemManager.registerSystem<S_Control>(static_cast<qe::SystemType>(System::Control));
	m_systemManager.registerSystem<S_GameUI>(static_cast<qe::SystemType>(System::GameUI));
	m_systemManager.registerSystem<S_Movement>(static_cast<qe::SystemType>(System::Movement));
	m_systemManager.registerSystem<S_Renderer>(static_cast<qe::SystemType>(System::Renderer));
	m_systemManager.registerSystem<S_Scoring>(static_cast<qe::SystemType>(System::Scoring));
	m_systemManager.registerSystem<S_SpriteAnimation>(static_cast<qe::SystemType>(System::SpriteAnimation));
	m_systemManager.registerSystem<S_State>(static_cast<qe::SystemType>(System::State));


	m_systemManager.getSystem<S_AI>(static_cast<qe::SystemType>(System::AI))->setRandomGenerator(&m_random);
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