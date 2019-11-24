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
	void PlayerMove(EventDetails* details);

	// Debug
	void ToggleOverlay(EventDetails* details);

private:
	void UpdateCamera();

	Map* m_gameMap;
	int m_player;
};