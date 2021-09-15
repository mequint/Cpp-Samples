#pragma once

#include "qe/ECS/C_Base.h"

#include "ECS/ECS_Types.h"

enum class eEntityType { PacMan, Ambusher, Chaser, Fickle, Ignorant, Dot, Pill, Fruit };

class C_EntityType : public qe::C_Base {
public:
	C_EntityType() : C_Base(static_cast<qe::ComponentType>(Component::EntityType)) {}

	void setEntityType(const eEntityType& entityType) { m_entityType = entityType; }
	eEntityType getEntityType() const { return m_entityType; }

private:
	eEntityType m_entityType;
};