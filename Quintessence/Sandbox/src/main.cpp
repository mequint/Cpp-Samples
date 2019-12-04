#include "TestApp.h"

int main() {
	TestApp app;

	while (!app.getWindow()->isDone()) {
		app.update();
		app.draw();
		app.postProcess();
	}

	return EXIT_SUCCESS;
}

// FEATURES:
// Update the Event Manager to load bindings via config file

// ARCHITECTURE:
// State Manager is currently tied to an enum class, this limits the state types that can be registered..
//		Consider replacing StateType with a string name