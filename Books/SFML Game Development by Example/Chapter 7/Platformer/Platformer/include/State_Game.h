#pragma once

#include "BaseState.h"
#include "EventManager.h"
#include "Map.h"

class State_Game : public BaseState {
public:
	State_Game(StateManager* stateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& time);
	void Draw();

	void MainMenu(EventDetails* details);
	void Pause(EventDetails* details);
	void ToggleOverlay(EventDetails* details);

private:
	Map* m_gameMap;
};