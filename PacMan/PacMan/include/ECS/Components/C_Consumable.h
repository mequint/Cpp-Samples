#pragma once

#include "qe/ECS/C_Base.h"
#include "ECS/ECS_Types.h"

class C_Consumable : public qe::C_Base {
public:
	C_Consumable() : C_Base(static_cast<qe::ComponentType>(Component::Consumable)) {}

private:
};