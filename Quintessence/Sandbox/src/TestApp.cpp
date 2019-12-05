#include "TestApp.h"

#include "TestState.h"

TestApp::TestApp() : 
	m_window("Test Application", sf::Vector2u(800, 600)),
	m_stateManager(&m_context) {

	m_elapsedTime = m_clock.restart();

	// Setup Context
	m_context.m_eventManager = m_window.getEventManager();
	m_context.m_stateManager = &m_stateManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_window = &m_window;

	// Register State Observers
	m_stateManager.registerObserver(m_context.m_eventManager);

	// Setup Bindings
	m_window.getEventManager()->addBinding("Window_Close", static_cast<int>(qe::EventType::Closed), 0);
	m_window.getEventManager()->addBinding("Key_Escape_Down", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Escape));
	m_window.getEventManager()->addBinding("Left_Button_Down", static_cast<int>(qe::EventType::MButtonDown), static_cast<int>(sf::Mouse::Button::Left));

	// Load Textures
	m_textureManager.loadResource("PacMan", "../media/Textures/PacMan.png");

	// Setup State
	m_stateManager.registerState<TestState>(qe::StateType::Game);

	// Change to first state
	m_stateManager.changeState(qe::StateType::Game);
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
