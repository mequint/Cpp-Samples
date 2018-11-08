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

// -Pre-Game State
// -Reset Game

// -Sound Manager
// -Add sound effects
// -Add Music

// Polish!
// -Fix Keyboard and Controller Responsiveness
// -Make the shape wait
// -Make font loading configurable
// -Make Event Manager bindings configurable via a file
// -Game State: "3,2,1.Go!" Animation - before game play
// -Add Lock functionality
// -Make block size configurable
// -Friendlier color scheme for grid and boxes
// -Make the grids lines and blocks glow
// -Project the light onto the grid
// -Add a "swoosh" animation when a shape is slammed
// -Cause the grid to light up when a "tetris" occurs
// -Particles in place of broken blocks
// -Build an animation system!!!
// -Make the Animated Message system a queue - play each message one at a time
// -Level Up Animated message
// -Combo Animated message
// -Gussy up the Title State background and titles
// -Gussy up the Messages
// -Animate the Game Over message (pop in should be fine - or maybe some sort of animation should occur in the grid)
// -Gussy up the Game State background
// -Add Combos to the scoring system
// -Update score based on time remaining till landing
// -Game Over state shows game stats
// -Tutorial State
// -Gussy up the Credits background