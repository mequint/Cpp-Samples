#include "State_MainMenu.h"

#include "GUI_Manager.h"
#include "StateManager.h"
#include "Window.h"

State_MainMenu::State_MainMenu(StateManager * stateManager) : BaseState(stateManager) {}
State_MainMenu::~State_MainMenu() = default;

void State_MainMenu::OnCreate() {
	GUI_Manager* gui = m_stateManager->GetContext()->m_guiManager;
	gui->LoadInterface(StateType::MainMenu, "MainMenu.interface", "MainMenu");
	gui->GetInterface(StateType::MainMenu, "MainMenu")->SetPosition(sf::Vector2f(250.0f, 168.0f));

	EventManager* eMgr = m_stateManager->GetContext()->m_eventManager;
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Play", &State_MainMenu::Play, this);
	eMgr->AddCallback(StateType::MainMenu, "MainMenu_Quit", &State_MainMenu::Quit, this);
}

void State_MainMenu::OnDestroy() {
	m_stateManager->GetContext()->m_guiManager->RemoveInterface(StateType::MainMenu, "MainMenu");

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::MainMenu, "MainMenu_Play");
	eventManager->RemoveCallback(StateType::MainMenu, "MainMenu_Quit");
}

void State_MainMenu::Activate() {
	auto& play = *m_stateManager->GetContext()->m_guiManager->GetInterface(StateType::MainMenu, "MainMenu")->GetElement("Play");

	if (m_stateManager->HasState(StateType::Game)) {
		play.SetText("RESUME");
	}
	else {
		play.SetText("PLAY");
	}
}

void State_MainMenu::Deactivate() {}
void State_MainMenu::Update(const sf::Time & time) {}

void State_MainMenu::Draw() {}

void State_MainMenu::Play(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::Game);
}

void State_MainMenu::Quit(EventDetails * details) {
	m_stateManager->GetContext()->m_window->Close();
}