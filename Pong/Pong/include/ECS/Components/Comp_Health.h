#pragma once

#include "qe\ECS\Core\Comp_Base.h"

class Comp_Health : public qe::Comp_Base {
public:
	Comp_Health() : qe::Comp_Base(Component::Health) {}

	unsigned int GetHealth() const { return m_health; }
	void SetHealth(unsigned int health) { m_health = health; }

	unsigned int GetMaxHealth() const { return m_maxHealth; }
	void SetMaxHealth(unsigned int maxHealth) { m_maxHealth = maxHealth; }

private:
	unsigned int m_health;
	unsigned int m_maxHealth;
};
