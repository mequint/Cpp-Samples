#include "State_GameOver.h"

#include "StateManager.h"
State_GameOver::State_GameOver(StateManager * stateManager) : BaseState(stateManager) {}
State_GameOver::~State_GameOver() {}

void State_GameOver::Create()
{
	auto* gameData = m_stateManager->GetContext()->m_gameData;
	sf::Font* font = m_stateManager->GetContext()->m_fontManager->GetFont("Game");

	m_result = Label(*font, 32); m_result.SetText("Results"); m_result.SetPosition(sf::Vector2f(10, 10));

	m_finalScore = Label(*font, 16); m_finalScore.SetText("Final Score - " + std::to_string(gameData->Score)); m_finalScore.SetPosition(sf::Vector2f(10, 52));
	m_finalLevel = Label(*font, 16); m_finalLevel.SetText("Final Level - " + std::to_string(gameData->Level)); m_finalLevel.SetPosition(sf::Vector2f(10, 78));

	m_singles = Label(*font, 16); m_singles.SetText("Singles - " + std::to_string(gameData->Singles)); m_singles.SetPosition(sf::Vector2f(10, 114));
	m_doubles = Label(*font, 16); m_doubles.SetText("Doubles - " + std::to_string(gameData->Doubles)); m_doubles.SetPosition(sf::Vector2f(10, 140));
	m_triples = Label(*font, 16); m_triples.SetText("Triples - " + std::to_string(gameData->Triples)); m_triples.SetPosition(sf::Vector2f(10, 166));
	m_quadruples = Label(*font, 16); m_quadruples.SetText("Quads  - " + std::to_string(gameData->Quadruples)); m_quadruples.SetPosition(sf::Vector2f(10, 192));
	m_lineTotal = Label(*font, 16); m_lineTotal.SetText("Total Lines - " + std::to_string(gameData->Lines)); m_lineTotal.SetPosition(sf::Vector2f(10, 218));

	m_combos = Label(*font, 16); m_combos.SetText("Combos - " + std::to_string(gameData->Combos)); m_combos.SetPosition(sf::Vector2f(10, 254));
	m_longestCombo = Label(*font, 16); m_longestCombo.SetText("Longest Combo - " + std::to_string(gameData->LongestCombo)); m_longestCombo.SetPosition(sf::Vector2f(10, 280));

	m_shapes = Label(*font, 16); m_shapes.SetText("Shapes"); m_shapes.SetPosition(sf::Vector2f(10, 316));
	m_i = Label(*font, 16); m_i.SetText("I Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::I])); m_i.SetPosition(sf::Vector2f(10, 342));
	m_j = Label(*font, 16); m_j.SetText("J Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::J])); m_j.SetPosition(sf::Vector2f(10, 368));
	m_l = Label(*font, 16); m_l.SetText("L Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::L])); m_l.SetPosition(sf::Vector2f(10, 394));
	m_o = Label(*font, 16); m_o.SetText("O Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::O])); m_o.SetPosition(sf::Vector2f(10, 420));
	m_s = Label(*font, 16); m_s.SetText("S Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::S])); m_s.SetPosition(sf::Vector2f(10, 446));
	m_t = Label(*font, 16); m_t.SetText("T Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::T])); m_t.SetPosition(sf::Vector2f(10, 472));
	m_z = Label(*font, 16); m_z.SetText("Z Blocks - " + std::to_string(gameData->ShapeCount[(int)ShapeType::Z])); m_z.SetPosition(sf::Vector2f(10, 498));

	m_returnMessage = Label(*font, 32); m_returnMessage.SetText("Press SPACE to continue"); m_returnMessage.SetPosition(sf::Vector2f(10, 550));

	auto* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->AddCallback(StateType::GameOver, "Key_Space", &State_GameOver::ReturnToTitle, this);
}

void State_GameOver::Destroy()
{
	auto* eventManager = m_stateManager->GetContext()->m_eventManager;
	eventManager->RemoveCallback(StateType::GameOver, "Key_Space");
}

void State_GameOver::Activate() {}
void State_GameOver::Deactivate() {}

void State_GameOver::Update(const sf::Time & time) {}

void State_GameOver::Draw()
{
	auto renderWindow = m_stateManager->GetContext()->m_window->GetRenderWindow();

	m_result.Draw(*renderWindow);
	m_finalScore.Draw(*renderWindow);
	m_finalLevel.Draw(*renderWindow);

	m_singles.Draw(*renderWindow);
	m_doubles.Draw(*renderWindow);
	m_triples.Draw(*renderWindow);
	m_quadruples.Draw(*renderWindow);
	m_lineTotal.Draw(*renderWindow);

	m_combos.Draw(*renderWindow);
	m_longestCombo.Draw(*renderWindow);

	m_shapes.Draw(*renderWindow);
	m_i.Draw(*renderWindow);
	m_j.Draw(*renderWindow);
	m_l.Draw(*renderWindow);
	m_o.Draw(*renderWindow);
	m_s.Draw(*renderWindow);
	m_t.Draw(*renderWindow);
	m_z.Draw(*renderWindow);

	m_returnMessage.Draw(*renderWindow);
}

void State_GameOver::ReturnToTitle(EventDetails * details)
{
	m_stateManager->GetContext()->m_gameData->Clear();
	m_stateManager->ChangeState(StateType::Title);
}