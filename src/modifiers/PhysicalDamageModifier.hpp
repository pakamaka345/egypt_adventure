//
// Created by pakamaka345 on 1/12/25.
//

#pragma once
#include "Modifier.hpp"

class PhysicalDamageModifier : public Modifier
{
private:
	float m_increasePhysDamage;

public:
	PhysicalDamageModifier(float increasePhysDamage) : m_increasePhysDamage(increasePhysDamage) {}

	float applyPhysicalDamage(float basePhys) const override
	{
		return basePhys + m_increasePhysDamage;
	}
};