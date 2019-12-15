#pragma once

#include "qe\ECS\EntityManager.h"

#include "Test_SystemManager.h"

class Test_EntityManager : public qe::EntityManager {
public:
	Test_EntityManager(Test_SystemManager* systemManager);

	virtual int addEntity(const qe::Bitmask& mask);
};