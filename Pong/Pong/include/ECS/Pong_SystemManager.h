#pragma once

#include "qe\ECS\Core\SystemManager.h"
#include "ECS\Systems\Systems.h"

class Pong_SystemManager : public qe::SystemManager {
public:
	virtual void Draw(qe::Window* window, unsigned int layer);
};