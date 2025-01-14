//
// Created by pakamaka345 on 1/12/25.
//

#pragma once
#include "Modifier.hpp"

class PriorityModifier : public Modifier
{
private:
	float m_increasePriority;

public:
	PriorityModifier(float increasePriority) : m_increasePriority(increasePriority) {}

	float applyPriority(float basePriority) const override
	{
		return basePriority + m_increasePriority;
	}
};