#include "State_Credits.h"

#include "StateManager.h"

State_Credits::State_Credits(StateManager * stateManager) : BaseState(stateManager) {}
State_Credits::~State_Credits() {}

void State_Credits::Create()
{
	m_font.loadFromFile("arial.ttf");

	std::string str[6];
	str[0] = "Programmed by: Michael E. Quint";
	str[1] = "Sound effects by: https://bassgorilla.com/video-game-sound-effects/";
	str[2] = "";
	str[3] = "Special thanks to Aleksey Pazhitnov";
	str[4] = "";
 	str[5] = "Press ENTER to Return to Title Screen";

	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();
	auto halfWinX = windowSize.x / 2;
	auto halfWinY = windowSize.y / 2;

	for (int i = 0; i < 6; ++i)
	{
		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(16);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		m_labels[i].setPosition(halfWinX, 250 + (i * 20 + 10));
	}

	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::Credits, "Key_Enter", &State_Credits::Title, this);
}

void State_Credits::Destroy()
{
	EventManager* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::Credits, "Key_Enter");
}

void State_Credits::Activate() {}
void State_Credits::Deactivate() {}
void State_Credits::Update(const sf::Time & time) {}

void State_Credits::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	for (int i = 0; i < 6; ++i)
	{
		window->draw(m_labels[i]);
	}
}

void State_Credits::Title(EventDetails * details)
{
	m_stateManager->ChangeState(StateType::Title);
}