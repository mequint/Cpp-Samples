#include "State_Paused.h"

#include "FontManager.h"
#include "StateManager.h"
#include "Window.h"

State_Paused::State_Paused(StateManager * stateManager) : BaseState(stateManager) {}
State_Paused::~State_Paused() = default;

void State_Paused::OnCreate() {
	SetTransparent(true);

	auto fontManager = m_stateManager->GetContext()->m_fontManager;

	m_text.setFont(*fontManager->GetResource("Main"));
	m_text.setString("PAUSED");
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0.0f, 0.0f);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() {
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;
	fontManager->ReleaseResource("Main");

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Activate() {}
void State_Paused::Deactivate() {}
void State_Paused::Update(const sf::Time & time) {}

void State_Paused::Draw() {
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_rect);
	window->draw(m_text);
}

void State_Paused::Unpause(EventDetails * details) {
	m_stateManager->SwitchTo(StateType::Game);
}