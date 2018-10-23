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

// Polish!
// -Make the grids lines and blocks glow
// -Project the light onto the grid

/*
***Shape Swap

- If Hold has No Shape
--Move Lander into Hold
--Create a new Lander
- Else
- Swap Hold with Lander
*Add a shape type of None to the Constructor, everything should work(by doing nothing)

***Slam
- Create a temp shape based on the Lander
- Move the temp shape down one
- Check to see if any of the blocks have gone over the top row
--If so, move one less
- Check to see if any of the blocks are intersecting a block in the grid
- If so, move one less
*Make usable for shadow cast

***Shadowcast
- Build a "shape" based on the vector pairs of the all the blocks in the shape
--Cull internal lines(this is determined by removing "doubled" lines)
- For all the pairs remainding
--Set the color outline based on the type
--Set the line thickness to an "appropriate" size
--Determine which pairs remain and draw the lines between them
- Project the shadow using the Slam function
*Easier: Create the piece using a more transparent version of the block...

*/
