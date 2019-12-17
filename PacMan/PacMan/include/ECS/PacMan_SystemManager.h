#pragma once

#include "qe\ECS\SystemManager.h"

class PacMan_SystemManager : public qe::SystemManager {
public:
	virtual void draw(qe::Window* window) override;
};