#pragma once

#include "qe/ECS/Core/Comp_Base.h"

class Comp_Controller : public qe::Comp_Base {
public:
	Comp_Controller() : Comp_Base(Component::Controller) {}
};