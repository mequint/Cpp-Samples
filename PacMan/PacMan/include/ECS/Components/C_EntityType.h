#pragma once

#include "qe/ECS/C_Base.h"

#include "ECS/ECS_Types.h"

enum class EntityType { PacMan, Dot, Pill, Fruit };

class C_EntityType : public qe::C_Base {
public:
	C_EntityType() : C_Base(static_cast<qe::ComponentType>(Component::EntityType)) {}

	void setEntityType(const EntityType& entityType) { m_entityType = entityType; }
	EntityType getEntityType() const { return m_entityType; }

private:
	EntityType m_entityType;
};