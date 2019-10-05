#include "Game.h"

#include "ECS\Components\Components.h"
#include "ECS\Systems\Systems.h"
#include "State\States\State_Game.h"
#include "State\States\State_Paused.h"

Game::Game() : 
	m_window("Pong", sf::Vector2u(800, 600)), 
	m_stateManager(&m_context), 
	m_entityManager(&m_systemManager),
	m_soundManager(&m_audioManager) {

	// Start the clock
	m_clock.restart();

	// Setup context
	m_systemManager.SetEntityManager(&m_entityManager);

	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_audioManager = &m_audioManager;
	m_context.m_fontManager = &m_fontManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_entityManager = &m_entityManager;
	m_context.m_systemManager = &m_systemManager;
	m_context.m_randomGenerator = &m_randomGenerator;
	m_context.m_soundManager = &m_soundManager;

	// Setup bindings
	SetupBindings();

	// Load sound files
	m_audioManager.AddResourcePath("Bleep", "media/audio/a5.wav");
	m_audioManager.AddResourcePath("Bloop", "media/audio/a4.wav");
	m_audioManager.LoadResource("Bleep");
	m_audioManager.LoadResource("Bloop");
	m_soundManager.AddSoundProperty("Bleep", 25.0f, 1.0f, 150, 2.0f);
	m_soundManager.AddSoundProperty("Bloop", 25.0f, 1.0f, 150, 2.0f);

	// Load fonts
	m_fontManager.AddResourcePath("Game", "media/fonts/arial.ttf");
	m_fontManager.LoadResource("Game");

	// Load textures
	m_textureManager.AddResourcePath("BluePaddle", "media/textures/BluePaddle.png");
	m_textureManager.AddResourcePath("RedPaddle", "media/textures/RedPaddle.png");
	m_textureManager.AddResourcePath("Ball", "media/textures/Ball.png");
	m_textureManager.LoadResource("BluePaddle");
	m_textureManager.LoadResource("RedPaddle");
	m_textureManager.LoadResource("Ball");

	// Setup ECS
	SetupECS();

	// Setup States
	m_stateManager.RegisterState<State_Game>(qe::StateType::Game);
	m_stateManager.RegisterState<State_Paused>(qe::StateType::Paused);

	m_stateManager.ChangeState(qe::StateType::Game);
}

void Game::SetupBindings() {
	m_window.GetEventManager()->AddBinding("CloseWindow", static_cast<int>(qe::EventType::Closed), 0);
	m_window.GetEventManager()->AddBinding("Key_Escape", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Escape));
	m_window.GetEventManager()->AddBinding("Key_Enter", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Return));
	m_window.GetEventManager()->AddBinding("Key_P", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::P));
	m_window.GetEventManager()->AddBinding("Key_Add", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Add));
	m_window.GetEventManager()->AddBinding("Key_Equal", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Equal));
	m_window.GetEventManager()->AddBinding("Key_Subtract", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Subtract));
	m_window.GetEventManager()->AddBinding("Key_Dash", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Dash));

	m_window.GetEventManager()->AddBinding("Key_Up", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Up));
	m_window.GetEventManager()->AddBinding("Key_Up_Released", static_cast<int>(qe::EventType::KeyUp), static_cast<int>(sf::Keyboard::Up));
	m_window.GetEventManager()->AddBinding("Key_W", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::W));
	m_window.GetEventManager()->AddBinding("Key_W_Released", static_cast<int>(qe::EventType::KeyUp), static_cast<int>(sf::Keyboard::W));
	m_window.GetEventManager()->AddBinding("Key_Left", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Left));
	m_window.GetEventManager()->AddBinding("Key_A", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::A));
	m_window.GetEventManager()->AddBinding("Key_Right", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Right));
	m_window.GetEventManager()->AddBinding("Key_D", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::D));
	m_window.GetEventManager()->AddBinding("Key_Down", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Down));
	m_window.GetEventManager()->AddBinding("Key_Down_Released", static_cast<int>(qe::EventType::KeyUp), static_cast<int>(sf::Keyboard::Down));
	m_window.GetEventManager()->AddBinding("Key_S", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::S));
	m_window.GetEventManager()->AddBinding("Key_S_Released", static_cast<int>(qe::EventType::KeyUp), static_cast<int>(sf::Keyboard::S));
	m_window.GetEventManager()->AddBinding("Key_Space", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Space));

	m_window.GetEventManager()->AddBinding("Left_Button_Down", static_cast<int>(qe::EventType::MButtonDown), static_cast<int>(sf::Mouse::Button::Left));
	m_window.GetEventManager()->AddBinding("Right_Button_Down", static_cast<int>(qe::EventType::MButtonDown), static_cast<int>(sf::Mouse::Button::Right));
}

void Game::SetupECS() {
	m_entityManager.RegisterComponent<Comp_Collider>(Component::Collider);
	m_entityManager.RegisterComponent<Comp_Health>(Component::Health);
	m_entityManager.RegisterComponent<Comp_SpecialAbility>(Component::SpecialAbility);
	m_entityManager.RegisterComponent<Comp_Position>(Component::Position);
	m_entityManager.RegisterComponent<Comp_Motion>(Component::Motion);
	m_entityManager.RegisterComponent<Comp_Controller>(Component::Controller);
	m_entityManager.RegisterComponent<Comp_Sprite>(Component::Sprite);
	m_entityManager.RegisterComponent<Comp_State>(Component::State);
	m_entityManager.RegisterComponent<Comp_PaddleAI>(Component::AIController);
	m_entityManager.RegisterComponent<Comp_SoundEmitter>(Component::SoundEmitter);

	m_systemManager.RegisterSystem<Sys_Renderer>(System::Renderer);
	m_systemManager.RegisterSystem<Sys_Movement>(System::Movement);
	m_systemManager.RegisterSystem<Sys_HUD>(System::HUD);
	m_systemManager.RegisterSystem<Sys_Control>(System::Control);
	m_systemManager.RegisterSystem<Sys_State>(System::State);
	m_systemManager.RegisterSystem<Sys_Collision>(System::Collision);
	m_systemManager.RegisterSystem<Sys_PaddleAI>(System::PaddleAI);
	m_systemManager.RegisterSystem<Sys_Sound>(System::Sound);

	auto windowSize = m_window.GetRenderWindow()->getSize();
	m_systemManager.GetSystem<Sys_Collision>(System::Collision)->SetBoundary(
		sf::FloatRect(sf::Vector2f(0.0f, 0.0f), static_cast<sf::Vector2f>(windowSize)));

	m_systemManager.GetSystem<Sys_HUD>(System::HUD)->Setup(windowSize.x, windowSize.y);

	m_systemManager.GetSystem<Sys_Sound>(System::Sound)->Setup(&m_audioManager, &m_soundManager);
}

Game::~Game() {}

void Game::Update() {
	m_window.Update();
	m_stateManager.Update(m_elapsedTime);
}

void Game::Draw() {
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::PostProcess() {
	m_stateManager.ProcessRequests();
	RestartClock();
}

sf::Time Game::GetElapsedtime() {
	return m_clock.getElapsedTime();
}

qe::Window* Game::GetWindow() {
	return &m_window;
}

/**************************************** Helper methods ****************************************/

void Game::RestartClock() {
	m_elapsedTime = m_clock.restart();
}