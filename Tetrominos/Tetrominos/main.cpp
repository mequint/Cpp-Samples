#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Draw();
		game.PostProcess();
	}

	return EXIT_SUCCESS;
}

// TODO:
// -Bug: Rotation collision detection may rotate a block into an already existing block...
// -Fine Tune: Scoring system
// -Fine Tune: Move Responsiveness/Controller Functionality

// -Add Animations
// --Block Removal
// -Add Message
// --Animation: Fade In/Fade Out
// --Level Up
// --Single
// --Double
// --Triple
// --Tetris!

// -Title State
// -Credit State
// -Pre-Game State
// -Reset Game

// -ResourceManager
// -FontManager

// -Sound Manager
// -Add sound effects
// -Add Music

// Polish!
// -Add Lock functionality
// -Make block size configurable
// -Friendlier color scheme for grid and boxes
// -Make the grids lines and blocks glow
// -Project the light onto the grid
// -Add a "swoosh" animation when a shape is slammed
// -Cause the grid to light up when a "tetris" occurs
// -Particles in place of broken blocks