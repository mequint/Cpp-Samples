#pragma once

#include "qe/ECS/Core/Comp_Base.h"

class Comp_PaddleAI : public qe::Comp_Base {
public:
	Comp_PaddleAI() : Comp_Base(Component::AIController) {}
};