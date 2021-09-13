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
// Update the Resource Manager to load bindings via config file

// ARCHITECTURE:
//	Move away from the enum/unsigned int based events
//	Add a state type string to the ECS to separate out entities per state