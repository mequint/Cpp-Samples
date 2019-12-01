#include "State_Game.h"

#include "DebugOverlay.h"
#include "EntityManager.h"
#include "StateManager.h"
#include "Window.h"

State_Game::State_Game(StateManager * stateManager) : BaseState(stateManager) {}
State_Game::~State_Game() = default;

void State_Game::OnCreate() {
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManager->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	eventManager->AddCallback(StateType::Game, "Key_O", &State_Game::ToggleOverlay, this);

	sf::Vector2u size = m_stateManager->GetContext()->m_window->GetWindowSize();
	m_view.setSize(static_cast<float>(size.x), static_cast<float>(size.y));
	m_view.setCenter(size.x / 2.0f, size.y / 2.0f);
	m_view.zoom(0.6f);

	m_stateManager->GetContext()->m_window->GetRenderWindow()->setView(m_view);

	m_gameMap = new Map(m_stateManager->GetContext(), this);
	m_gameMap->LoadMap("media/Maps/map1.map");
}

void State_Game::OnDestroy() {
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Game, "Key_Escape");
	eventManager->RemoveCallback(StateType::Game, "Key_P");
	eventManager->RemoveCallback(StateType::Game, "Key_O");

	delete m_gameMap;
	m_gameMap = nullptr;
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time & time) {
	SharedContext* context = m_stateManager->GetContext();
	EntityBase* player = context->m_entityManager->Find("Player");
	
	if (!player) {
		std::cout << "Respawning player..." << std::endl;

		context->m_entityManager->Add(EntityType::Player, "Player");
		player = context->m_entityManager->Find("Player");
		player->SetPosition(m_gameMap->GetPlayerStart());
	}
	else {
		m_view.setCenter(player->GetPosition());
		context->m_window->GetRenderWindow()->setView(m_view);
	}

	sf::FloatRect viewSpace = context->m_window->GetViewSpace();
	if (viewSpace.left <= 0.0f) {
		m_view.setCenter(viewSpace.width / 2.0f, m_view.getCenter().y);
		context->m_window->GetRenderWindow()->setView(m_view);
	}
	else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) {
		m_view.setCenter(((m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2.0f), m_view.getCenter().y);
		context->m_window->GetRenderWindow()->setView(m_view);
	}

	m_gameMap->Update(time.asSeconds());
	m_stateManager->GetContext()->m_entityManager->Update(time.asSeconds());
}

void State_Game::Draw() {
	m_gameMap->Draw();
	m_stateManager->GetContext()->m_entityManager->Draw();
}

void State_Game::MainMenu(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::Paused);
}

void State_Game::ToggleOverlay(EventDetails * details) {
	m_stateManager->GetContext()->m_debugOverlay->SetDebug(!m_stateManager->GetContext()->m_debugOverlay->Debug());
}