#include "ECS/Systems/S_GameUI.h"

#include "ECS/ECS_Types.h"
#include "ECS/PacMan_SystemManager.h"
#include "ECS/Components/C_Score.h"

S_GameUI::S_GameUI(qe::SystemManager* systemManager) :
	qe::S_Base(static_cast<qe::SystemType>(System::GameUI), systemManager) {
	qe::Bitmask req;
	req.set(static_cast<qe::ComponentType>(Component::Score));
	m_requiredComponents.push_back(req);

	PacMan_SystemManager* systems = dynamic_cast<PacMan_SystemManager*>(m_systemManager);

	auto windowSize = systems->getWindow()->getRenderWindow()->getSize();

	m_scoreLabel.setFont(*systems->getFontManager()->getResource("Game"));
	m_scoreLabel.setCharacterSize(16);
	m_scoreLabel.setString("SCORE");
	m_scoreLabel.setStyle(sf::Text::Bold);
	m_scoreLabel.setOrigin(m_scoreLabel.getGlobalBounds().width / 2.0f, 0.0f);
	m_scoreLabel.setPosition(windowSize.x / 2.0f, 14.0f);

	m_score.setFont(*systems->getFontManager()->getResource("Game"));
	m_score.setCharacterSize(16);
	m_score.setString("0");
	m_score.setStyle(sf::Text::Bold);
	m_score.setOrigin(m_score.getGlobalBounds().width / 2.0f, 0.0f);
	m_score.setPosition(windowSize.x / 2.0f, 32.0f);
}

S_GameUI::~S_GameUI() {
}

void S_GameUI::notify(const qe::Message & message) {
}

void S_GameUI::update(float dt) {
	auto entities = m_systemManager->getEntityManager();
	
	PacMan_SystemManager* systems = dynamic_cast<PacMan_SystemManager*>(m_systemManager);
	auto windowSize = systems->getWindow()->getRenderWindow()->getSize();

	for (auto& entity : m_entities) {
		C_Score* score = entities->getComponent<C_Score>(entity, static_cast<qe::ComponentType>(Component::Score));
		if (score) {
			m_score.setString(std::to_string(score->getScore()));
			m_score.setOrigin(m_score.getGlobalBounds().width / 2.0f, 0.0f);
			m_score.setPosition(windowSize.x / 2.0f, 32.0f);
		}
	}
}

void S_GameUI::handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) {
}

void S_GameUI::render(qe::Window * window) {
	auto renderer = window->getRenderWindow();

	renderer->draw(m_score);
	renderer->draw(m_scoreLabel);
}