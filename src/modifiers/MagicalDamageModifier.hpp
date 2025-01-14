//
// Created by pakamaka345 on 1/12/25.
//

#pragma once
#include "Modifier.hpp"

class MagicalDamageModifier : public Modifier
{
private:
	float m_increaseMagicDamage;

public:
	MagicalDamageModifier(float increaseMagicDamage) : m_increaseMagicDamage(increaseMagicDamage) {}

	float applyMagicalDamage(float baseMagic) const override
	{
		return baseMagic + m_increaseMagicDamage;
	}
};

