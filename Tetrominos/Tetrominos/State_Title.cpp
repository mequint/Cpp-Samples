#include "State_Title.h"

#include "StateManager.h"

State_Title::State_Title(StateManager * stateManager) : BaseState(stateManager)
{}

State_Title::~State_Title() {}

void State_Title::Create()
{
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();

	m_font.loadFromFile("arial.ttf");

	// Set title
	m_titleText.setFont(m_font);
	m_titleText.setString(sf::String("Linebreaker"));
	m_titleText.setCharacterSize(60);

	sf::FloatRect titleRect = m_titleText.getLocalBounds();
	m_titleText.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
	m_titleText.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f - titleRect.height / 2.0f);

	// Set subtitle
	m_subTitle.setFont(m_font);
	m_subTitle.setString(sf::String("Press SPACE to begin"));
	m_subTitle.setCharacterSize(16);

	sf::FloatRect subTitleRect = m_subTitle.getLocalBounds();
	m_subTitle.setOrigin(subTitleRect.left + subTitleRect.width / 2.0f, subTitleRect.top + subTitleRect.height / 2.0f);
	m_subTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f + windowSize.y / 5);

	// Set up callbacks
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Title, "Key_Space", &State_Title::Continue, this);
	eventManager->AddCallback(StateType::Title, "Key_Enter", &State_Title::Credits, this);
}

void State_Title::Destroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Title, "Key_Space");
	eventManager->RemoveCallback(StateType::Title, "Key_Enter");
}

void State_Title::Activate() {}
void State_Title::Deactivate() {}

void State_Title::Update(const sf::Time & time) {}

void State_Title::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	window->draw(m_titleText);
	window->draw(m_subTitle);
}

void State_Title::Continue(EventDetails* details)
{
	m_stateManager->ChangeState(StateType::Game);
}

void State_Title::Credits(EventDetails * details)
{
	m_stateManager->ChangeState(StateType::Credits);
}