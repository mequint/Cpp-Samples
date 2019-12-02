#include "qe/Window/Window.h"

int main() {
	qe::Window window("Hello", sf::Vector2u(800, 600));
	window.setCursor("../media/Cursors/SwordCursor.png", sf::Vector2u(0, 16));

	while (!window.isDone()) {
		window.update();

		window.beginDraw();
		window.endDraw();
	}

	return EXIT_SUCCESS;
}