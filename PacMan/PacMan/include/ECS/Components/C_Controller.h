#pragma once

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Controller : public qe::C_Base {
public:
	C_Controller() : C_Base(static_cast<qe::ComponentType>(Component::Controller)) {}
};