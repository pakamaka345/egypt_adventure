//
// Created by pakamaka345 on 1/15/25.
//

#pragma once
#include "Amulet.hpp"

class DefenseModifier;
class DodgeChanceModifier;

class ArmorAmulets : public Amulet {
private:
	float m_defense;
	float m_dodgeChance;

	std::shared_ptr<DefenseModifier> m_defenseModifier;
	std::shared_ptr<DodgeChanceModifier> m_dodgeChanceModifier;

public:
	ArmorAmulets(float defense, float dodgeChance);

	void applyAmuletEffect(Entity& target) override;
	void removeAmuletEffect(Entity& target) override;
};


