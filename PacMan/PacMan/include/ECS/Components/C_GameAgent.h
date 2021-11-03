#pragma once

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_GameAgent : public qe::C_Base {
public:
	C_GameAgent() : qe::C_Base(static_cast<qe::ComponentType>(Component::GameAgent)) {}
};