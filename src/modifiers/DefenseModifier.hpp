//
// Created by pakamaka345 on 1/12/25.
//

#pragma once
#include "Modifier.hpp"

class DefenseModifier : public Modifier
{
private:
	float m_increaseDefense;

public:
	DefenseModifier(float increaseDefense) : m_increaseDefense(increaseDefense) {}

	float applyDefense(float baseDefense) const override
	{
		return baseDefense + m_increaseDefense;
	}
};