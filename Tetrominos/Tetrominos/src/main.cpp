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
// -Bug: Multiple combos are not being picked up correctly...

// -Sound Manager
// -Add sound effects
// -Add Music

// --------------
// Polish!
// --------------

// -Controls
// --Fix Keyboard and Controller Responsiveness
// --Make Event Manager bindings configurable via a file

// -Engine
// --Make font loading configurable
// --Handle screen resizing and focus

// -Game Play
// --Make the shape wait
// --Add Lock functionality at the bottom of the grid (signifies Shape state)
// --Add Lock functionality at the top of the grid (signifies Shape state)
// --Update score based on time remaining till landing

// -Communication
// --Game State: "3,2,1.Go!" Animation - before game play
// --Add a "swoosh" animation when a shape is slammed
// --Cause the grid to light up when a "quadruple" occurs
// --Particles in place of broken blocks
// --Animate the Game Over message (pop in should be fine - or maybe some sort of animation should occur in the grid)
// --Message animation should pop in, then shoot off the screen

// -Graphics
// --Make block size configurable
// --Make the grids lines and blocks glow
// --Friendlier color scheme for grid and boxes
// --Gussy up the Title State background and titles
// --Gussy up the Messages
// --Gussy up the Game State background
// --Gussy up the Credits background
// --Gussy up the Game State UI
// --Gussy up the Game Over State

// -Sound
// --Speed up music when shape gets too close to the top
// --Add move sound
// --Add rotate sound
// --Add hold sound
// --Level Up sound

// -States
// --Pre-Game State
// --Tutorial State

// -Dreaming
// --Build an animation system!!!