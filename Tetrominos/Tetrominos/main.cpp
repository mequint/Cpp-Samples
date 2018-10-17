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

// TODO
// -Bug: The Shape draw only works in context of the Grid.  Make it work outside of the grid context.
// -Make the Shape appear into the Next box
// -Move the Shape to grid once the last one landed
// -Add a Score textbox
// -Add a Level textbox
// -Fine tune the drop speed per level