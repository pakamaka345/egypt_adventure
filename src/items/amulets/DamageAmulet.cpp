//
// Created by pakamaka345 on 1/14/25.
//

#include "DamageAmulet.hpp"
#include "modifiers/PhysicalDamageModifier.hpp"
#include "modifiers/MagicalDamageModifier.hpp"
#include <entities/Entity.hpp>

DamageAmulet::DamageAmulet(float physicalDamage, float magicalDamage, int levelIndex)
	: Amulet("Amulet of Strength", "Magical amulets. They were a gift for a pharaon. He had never worn them.", 0, 0, levelIndex, 's'), m_physicalDamage(physicalDamage), m_magicalDamage(magicalDamage)
{
}

void DamageAmulet::applyAmuletEffect(Entity& target)
{
	if (m_physicalDamage > 0) {
		m_physicalDamageModifier = std::make_shared<PhysicalDamageModifier>(m_physicalDamage);
		target.addModifier(m_physicalDamageModifier);
	}
	if (m_magicalDamage > 0) {
		m_magicalDamageModifier = std::make_shared<MagicalDamageModifier>(m_magicalDamage);
		target.addModifier(m_magicalDamageModifier);
	}
}

void DamageAmulet::removeAmuletEffect(Entity& target)
{
	if (m_physicalDamageModifier != nullptr) {
		target.removeModifier(m_physicalDamageModifier);
	}
	if (m_magicalDamageModifier != nullptr) {
		target.removeModifier(m_magicalDamageModifier);
	}
}


