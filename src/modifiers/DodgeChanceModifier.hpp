//
// Created by pakamaka345 on 1/12/25.
//

#pragma once
#include "Modifier.hpp"

class DodgeChanceModifier : public Modifier
{
private:
	float m_increaseDodgeChance;

public:
	DodgeChanceModifier(float increaseDodgeChance) : m_increaseDodgeChance(increaseDodgeChance) {}

	float applyDodgeChance(float baseDodge) const override
	{
		return baseDodge + m_increaseDodgeChance;
	}
};