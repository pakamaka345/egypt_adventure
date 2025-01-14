//
// Created by pakamaka345 on 1/12/25.
//

#pragma once
#include "Modifier.hpp"

class HealthModifier : public Modifier
{
private:
	float m_increaseHealth;

public:
	HealthModifier(float increaseHealth) : m_increaseHealth(increaseHealth) {}

	float applyHealth(float baseHealth) const override
	{
		return baseHealth + m_increaseHealth;
	}
};