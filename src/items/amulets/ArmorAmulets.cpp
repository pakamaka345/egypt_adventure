//
// Created by pakamaka345 on 1/15/25.
//

#include "ArmorAmulets.hpp"
#include "entities/Entity.hpp"
#include <modifiers/DefenseModifier.hpp>
#include <modifiers/DodgeChanceModifier.hpp>

ArmorAmulets::ArmorAmulets(float defense, float dodgeChance, int levelIndex)
	: Amulet("amulet of defense", "Magical amulets. They were a gift for a pharaon. He had never worn them.", 0, 0, levelIndex, 'd'), m_defense(defense), m_dodgeChance(dodgeChance)
{
}

void ArmorAmulets::applyAmuletEffect(Entity& target)
{
	if (m_defense > 0) {
		m_defenseModifier = std::make_shared<DefenseModifier>(m_defense);
		target.addModifier(m_defenseModifier);
	}
    if (m_dodgeChance > 0) {
    	m_dodgeChanceModifier = std::make_shared<DodgeChanceModifier>(m_dodgeChance);
		target.addModifier(m_dodgeChanceModifier);
	}
}

void ArmorAmulets::removeAmuletEffect(Entity& target)
{
	if (m_defenseModifier != nullptr) {
		target.removeModifier(m_defenseModifier);
	}
	if (m_dodgeChanceModifier != nullptr) {
		target.removeModifier(m_dodgeChanceModifier);
	}
}

std::string ArmorAmulets::getSpecifications()
{
	std::string specs = "Defense: " + std::to_string(m_defense) + "\n";
	specs += "Dodge chance: " + std::to_string(m_dodgeChance) + "\n";
	return specs;
}


