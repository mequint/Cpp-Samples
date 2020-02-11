#pragma once

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Points : public qe::C_Base {
public:
	C_Points() : qe::C_Base(static_cast<qe::ComponentType>(Component::Points)) {}

	void setPoints(unsigned int points) { m_points = points; }
	unsigned int getPoints() const { return m_points; }

private:
	unsigned int m_points;
};