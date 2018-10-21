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

// -Add Slam Functionality
// --Add Block Shadow
// -Add Hold Functionality
// -Spawn shape based on its type

// -Update control scheme to allow for better movement
// -Add Controller Functionality
// -Friendlier color scheme for grid and boxes

// -Pause State
// --Event Manager
// -Title State
// -Credit State
// -Pre-Game State
// -Game Over
// --Add lose condition check

// -Sound Manager
// -Add sound effects
// -Add Music

// -Add Animations
// --Block Removal
// -Add Message
// --Animation: Fade In/Fade Out
// --Level Up
// --Single
// --Double
// --Triple
// --Tetris!