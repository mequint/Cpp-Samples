#include "State/States/State_Paused.h"

#include "qe/Resources/FontManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

State_Paused::State_Paused(qe::StateManager* stateManager) : BaseState(stateManager) {}
State_Paused::~State_Paused() = default;

void State_Paused::Create() {
	SetTransparent(true);

	sf::Font* font = m_stateManager->GetContext()->m_fontManager->GetResource("Game");
	m_text.setFont(*font);
	m_text.setString(sf::String("PAUSED"));
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0.0f, 0.0f);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	qe::EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(qe::StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::Destroy() {
	qe::EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(qe::StateType::Paused, "Key_P");
}

void State_Paused::Activate()  {
	m_timePassed = 0.0f;
}

void State_Paused::Deactivate() {}

void State_Paused::Update(const sf::Time & time) {
	m_timePassed += time.asSeconds();
	if (m_timePassed < 3.0f)
	{
		m_hidden = false;
	}
	else if (m_timePassed < 4.0f)
	{
		m_hidden = true;
	}
	else
	{
		m_hidden = false;
		m_timePassed = 0.0f;
	}
}

void State_Paused::Draw() {
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_rect);

	if (!m_hidden)
	{
		window->draw(m_text);
	}
}

void State_Paused::Unpause(qe::EventDetails * details) {
	m_stateManager->ChangeState(qe::StateType::Game);
}