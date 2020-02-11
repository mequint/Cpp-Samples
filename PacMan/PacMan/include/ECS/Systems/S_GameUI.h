#pragma once

#include <SFML/Graphics/Text.hpp>

#include "qe/ECS/S_Base.h"
#include "qe/Window/Window.h"

class S_GameUI : public qe::S_Base {
public:
	S_GameUI(qe::SystemManager* systemManager);
	~S_GameUI();

	// Inherited via S_Base
	virtual void notify(const qe::Message & message) override;
	virtual void update(float dt) override;
	virtual void handleEvent(const qe::EntityId & entityId, const qe::EntityEventType & event) override;

	void render(qe::Window* window);

private:
	sf::Text m_scoreLabel;
	sf::Text m_score;
};