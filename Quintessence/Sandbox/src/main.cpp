#include "qe/Window/Window.h"

int main() {
	qe::Window window("Hello", sf::Vector2u(800, 600));
	window.setCursor("../media/Cursors/SwordCursor.png", sf::Vector2u(0, 16));
	//window.setCursor(qe::CursorType::Text);
	
	window.getEventManager()->addBinding("Window_Close", static_cast<int>(qe::EventType::Closed), 0);
	window.getEventManager()->addBinding("Key_Escape_Down", static_cast<int>(qe::EventType::KeyDown), static_cast<int>(sf::Keyboard::Escape));
	window.getEventManager()->addBinding("Left_Button_Down", static_cast<int>(qe::EventType::MButtonDown), static_cast<int>(sf::Mouse::Button::Left));

	while (!window.isDone()) {
		window.update();

		window.beginDraw();
		window.endDraw();
	}

	return EXIT_SUCCESS;
}

// FEATURES:
// Update the Event Manager to load bindings via config file