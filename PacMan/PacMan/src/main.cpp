#include "Game.h"

int main() {
	Game game;

	while (!game.getWindow()->isDone()) {
		game.update();
		game.draw();
		game.postProcess();
	}

	return EXIT_SUCCESS;
}