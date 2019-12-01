#include "State_Game.h"

#include "GUI_Manager.h"
#include "StateManager.h"
#include "SystemManager.h"
#include "Window.h"

State_Game::State_Game(StateManager * stateManager) : BaseState(stateManager) {}
State_Game::~State_Game() = default;

void State_Game::OnCreate() {
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;

	eventManager->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManager->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);
	eventManager->AddCallback(StateType::Game, "Player_MoveLeft", &State_Game::PlayerMove, this);
	eventManager->AddCallback(StateType::Game, "Player_MoveRight", &State_Game::PlayerMove, this);
	eventManager->AddCallback(StateType::Game, "Player_MoveUp", &State_Game::PlayerMove, this);
	eventManager->AddCallback(StateType::Game, "Player_MoveDown", &State_Game::PlayerMove, this);

	sf::Vector2u size = m_stateManager->GetContext()->m_window->GetWindowSize();
	m_view.setSize(static_cast<float>(size.x), static_cast<float>(size.y));
	m_view.setCenter(size.x / 2.0f, size.y / 2.0f);
	m_view.zoom(0.6f);

	m_stateManager->GetContext()->m_window->GetRenderWindow()->setView(m_view);

	m_gameMap = new Map(m_stateManager->GetContext());
	m_gameMap->LoadMap("media/Maps/map1.map");

	EntityManager* entities = m_stateManager->GetContext()->m_entityManager;
	m_stateManager->GetContext()->m_systemManager->GetSystem<S_Collision>(System::Collision)->SetMap(m_gameMap);
	m_stateManager->GetContext()->m_systemManager->GetSystem<S_Movement>(System::Movement)->SetMap(m_gameMap);
	m_player = m_gameMap->GetPlayerId();

	m_stateManager->GetContext()->m_soundManager->PlayMusic("TownTheme", 50.0f, true);
}

void State_Game::OnDestroy() {
	m_stateManager->GetContext()->m_guiManager->RemoveInterface(StateType::Game, "Test");

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_Escape");
	eventManager->RemoveCallback(StateType::Game, "Key_O");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveLeft");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveRight");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveUp");
	eventManager->RemoveCallback(StateType::Game, "Player_MoveDown");

	delete m_gameMap;
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time & time) {
	SharedContext* context = m_stateManager->GetContext();
	UpdateCamera();

	m_gameMap->Update(time.asSeconds());
	context->m_systemManager->Update(time.asSeconds());
}

void State_Game::Draw() {
	for (unsigned int i = 0; i < Sheet::Num_Layers; ++i) {
		m_gameMap->Draw(i);
		m_stateManager->GetContext()->m_systemManager->Draw(m_stateManager->GetContext()->m_window, i);
	}
}

void State_Game::MainMenu(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::Paused);
}

void State_Game::PlayerMove(EventDetails * details) {
	Message message(static_cast<MessageType>(EntityMessage::Move));

	if (details->m_name == "Player_MoveLeft") {
		message.m_int = static_cast<int>(Direction::Left);
	}
	else if (details->m_name == "Player_MoveRight") {
		message.m_int = static_cast<int>(Direction::Right);
	}
	else if (details->m_name == "Player_MoveUp") {
		message.m_int = static_cast<int>(Direction::Up);
	}
	else if (details->m_name == "Player_MoveDown") {
		message.m_int = static_cast<int>(Direction::Down);
	}

	message.m_receiver = m_player;
	m_stateManager->GetContext()->m_systemManager->GetMessageHandler()->Dispatch(message);
}

void State_Game::ToggleOverlay(EventDetails * details) {
	m_stateManager->GetContext()->m_debugOverlay->SetDebug(!m_stateManager->GetContext()->m_debugOverlay->Debug());
}

void State_Game::UpdateCamera() {
	if (m_player == -1) return;

	SharedContext* context = m_stateManager->GetContext();
	C_Position* pos = m_stateManager->GetContext()->m_entityManager->GetComponent<C_Position>(m_player, Component::Position);

	m_view.setCenter(pos->GetPosition());
	context->m_window->GetRenderWindow()->setView(m_view);

	sf::FloatRect viewSpace = context->m_window->GetViewSpace();
	if (viewSpace.left <= 0.0f) {
		m_view.setCenter(viewSpace.width / 2.f, m_view.getCenter().y);
		context->m_window->GetRenderWindow()->setView(m_view);
	}
	else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x) * Sheet::Tile_Size) {
		m_view.setCenter((m_gameMap->GetMapSize().x * Sheet::Tile_Size) - (viewSpace.width / 2.0f),
			m_view.getCenter().y);
		context->m_window->GetRenderWindow()->setView(m_view);
	}

	if (viewSpace.top <= 0.0f) {
		m_view.setCenter(m_view.getCenter().x, viewSpace.height / 2.0f);
		context->m_window->GetRenderWindow()->setView(m_view);
	}
	else if (viewSpace.top + viewSpace.height > m_gameMap->GetMapSize().y * Sheet::Tile_Size) {
		m_view.setCenter(m_view.getCenter().x, (m_gameMap->GetMapSize().y * Sheet::Tile_Size - viewSpace.height / 2.0f));
		context->m_window->GetRenderWindow()->setView(m_view);
	}
}