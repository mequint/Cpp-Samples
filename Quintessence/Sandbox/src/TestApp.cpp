#include "TestApp.h"

#include "ECS/Components/Components.h"
#include "ECS/Systems/Systems.h"

#include "qe/Window/EventLoader.h"

#include "StateTypes.h"
#include "NextState.h"
#include "TestState.h"

TestApp::TestApp() : 
	m_window("Test Application", sf::Vector2u(800, 600)),
	m_stateManager(&m_context),
	m_entityManager(&m_systemManager) {

	m_elapsedTime = m_clock.restart();

	// Setup Context
	m_context.m_entityManager = &m_entityManager;
	m_context.m_eventManager = m_window.getEventManager();
	m_context.m_fontManager = &m_fontManager;
	m_context.m_stateManager = &m_stateManager;
	m_context.m_systemManager = &m_systemManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_window = &m_window;

	// Register State Observers
	m_stateManager.registerObserver(m_context.m_eventManager);

	// Setup Bindings
	qe::EventLoader loader(m_window.getEventManager());
	loader.loadFromJsonFile(qe::Utils::getWorkingDirectory() + "../media/eventBindings.json");

	// Load Textures
	m_textureManager.loadResource("PacMan", "../media/Textures/PacMan.png");
	m_textureManager.loadResource("AnimatedPacMan", "../media/Textures/AnimatedPacMan.png");

	// Load Fonts
	m_fontManager.loadResource("Game", "../media/Fonts/Vegur-Regular.otf");

	// Setup ECS
	m_systemManager.setEntityManager(&m_entityManager);

	m_entityManager.registerComponent<C_Position>(static_cast<qe::ComponentType>(Component::Position));
	m_entityManager.registerComponent<C_Sprite>(static_cast<qe::ComponentType>(Component::Sprite));
	
	m_systemManager.registerSystem<S_Renderer>(static_cast<qe::SystemType>(System::Renderer));

	// Setup State
	m_stateManager.registerState<TestState>(StateType::Game);
	m_stateManager.registerState<NextState>(StateType::NextState);

	// Change to first state
	m_stateManager.changeState(StateType::Game);
}

void TestApp::update() {
	m_window.update();
	m_stateManager.update(m_elapsedTime);
}

void TestApp::draw() {
	m_window.beginDraw();
	m_stateManager.draw();
	m_window.endDraw();
}

void TestApp::postProcess() {
	m_stateManager.removeDeadStates();
	m_elapsedTime = m_clock.restart();
}

qe::Window * TestApp::getWindow() {
	return &m_window;
}