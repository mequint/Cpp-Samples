#pragma once

#include "qe\ECS\Core\Comp_Base.h"
#include "Game Data\SpecialAbility.h"


class Comp_SpecialAbility : public qe::Comp_Base {
public:
	Comp_SpecialAbility() : qe::Comp_Base(Component::SpecialAbility) {}

	void SetSpecialPoints(unsigned int specialPoints) { m_specialPoints = specialPoints; }
	unsigned int GetSpecialPoints() const { return m_specialPoints; }

	void SetMaxSpecialPoints(unsigned int specialPoints) { m_maxSpecialPoints = specialPoints; }
	unsigned int GetMaxSpecialPoints() const { return m_maxSpecialPoints; }

	void SetSpecialAbility(const SpecialAbility& ability) { m_ability = ability; }
	SpecialAbility GetSpecialAbility() const { return m_ability; }

private:
	unsigned int m_specialPoints;
	unsigned int m_maxSpecialPoints;

	SpecialAbility m_ability;
};