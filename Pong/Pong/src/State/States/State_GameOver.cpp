#include "State/States/State_GameOver.h"

#include "qe/Resources/FontManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

State_GameOver::State_GameOver(qe::StateManager * stateManager) : BaseState(stateManager) {}
State_GameOver::~State_GameOver() = default;

void State_GameOver::Create() {
	SetTransparent(true);

	auto font = m_stateManager->GetContext()->m_fontManager->GetResource("Game");
	m_text.setFont(*font);
	m_text.setString(sf::String("GAME OVER"));
	m_text.setCharacterSize(20);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0.0f, 0.0f);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));
}

void State_GameOver::Destroy() {}
void State_GameOver::Activate() {}
void State_GameOver::Deactivate() {}
void State_GameOver::Update(const sf::Time & time) {}

void State_GameOver::Draw() {
	auto window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_rect);
	window->draw(m_text);
}