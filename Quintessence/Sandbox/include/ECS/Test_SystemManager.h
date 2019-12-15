#pragma once

#include "qe\ECS\SystemManager.h"

class Test_SystemManager : public qe::SystemManager {
public:
	// Inherited via SystemManager
	virtual void draw(qe::Window * window) override;
};