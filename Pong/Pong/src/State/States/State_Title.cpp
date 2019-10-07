#include "State/States/State_Title.h"

#include "qe/Resources/FontManager.h"
#include "qe/State/StateManager.h"
#include "qe/Window/Window.h"

State_Title::State_Title(qe::StateManager* stateManager) : qe::BaseState(stateManager) {}
State_Title::~State_Title() = default;

void State_Title::Create() {
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	sf::Font* font = m_stateManager->GetContext()->m_fontManager->GetResource("Game");

	// Set title
	m_titleText.setFont(*font);
	m_titleText.setString(sf::String("Battle Pong"));
	m_titleText.setCharacterSize(60);

	sf::FloatRect titleRect = m_titleText.getLocalBounds();
	m_titleText.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	m_titleText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - titleRect.height / 2.0f);

	// Set subtitle
	m_subtitleText.setFont(*font);
	m_subtitleText.setString(sf::String("Press SPACE to begin"));
	m_subtitleText.setCharacterSize(16);

	sf::FloatRect subTitleRect = m_subtitleText.getLocalBounds();
	m_subtitleText.setOrigin(subTitleRect.left + subTitleRect.width / 2.0f, subTitleRect.top + subTitleRect.height / 2.0f);
	m_subtitleText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + windowSize.y / 5);

	// Set up callbacks
	qe::EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(qe::StateType::Title, "Key_Space", &State_Title::Continue, this);
}

void State_Title::Destroy() {
	qe::EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(qe::StateType::Title, "Key_Space");
}

void State_Title::Activate() {}
void State_Title::Deactivate() {}

void State_Title::Update(const sf::Time & time) {}

void State_Title::Draw() {
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	window->draw(m_titleText);
	window->draw(m_subtitleText);
}

void State_Title::Continue(qe::EventDetails * details) {
	m_stateManager->ChangeState(qe::StateType::Game);
}