//
// Created by pakamaka345 on 1/12/25.
//

#pragma once

class Modifier
{
public:
	virtual float applyHealth(float baseHealth) const { return baseHealth; }
	virtual float applyPhysicalDamage(float basePhys) const { return basePhys; }
	virtual float applyMagicalDamage(float baseMagic) const { return baseMagic; }
	virtual float applyPriority(float basePriority) const { return basePriority; }
	virtual float applyDodgeChance(float baseDodge) const { return baseDodge; }
	virtual float applyDefense(float baseDefense) const { return baseDefense; }
	virtual ~Modifier() = default;
};