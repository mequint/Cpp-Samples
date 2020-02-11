#pragma once

#include "ECS/ECS_Types.h"
#include "qe/ECS/C_Base.h"

class C_Score : public qe::C_Base {
public:
	C_Score() : C_Base(static_cast<qe::ComponentType>(Component::Score)) {}

	void setScore(unsigned int score) { m_score = score; }
	unsigned int getScore() const { return m_score; }

private:
	unsigned int m_score;
};