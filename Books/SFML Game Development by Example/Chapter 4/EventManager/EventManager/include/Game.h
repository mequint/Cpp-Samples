#pragma once

#include "EventManager.h"
#include "Window.h"

class Game {
public:
	Game();
	~Game();

	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

	void MoveSprite(EventDetails* details);

private:
	Window m_window;
	sf::Clock m_clock;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};