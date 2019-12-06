#pragma once

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "qe/State/BaseState.h"
#include "qe/Window/EventDetails.h"

#include "Tile/TileMapManager.h"

class State_Game : public qe::BaseState {
public:
	State_Game(qe::StateManager* stateManager);

	// Inherited via BaseState
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(const sf::Time & time) override;
	virtual void draw() override;

	// Callbacks
	void onPause(qe::EventDetails* details);
	void onQuit(qe::EventDetails* details);
	void onMove(qe::EventDetails* details);

private:
	TileMapManager m_tileMapManager;

	sf::Texture m_tileTexture;
	sf::Sprite m_mapSprite;
};