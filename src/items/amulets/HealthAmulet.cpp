//
// Created by pakamaka345 on 1/15/25.
//

#include "HealthAmulet.hpp"

#include <entities/Entity.hpp>

#include "modifiers/HealthModifier.hpp"

HealthAmulet::HealthAmulet(float maxHealth, int levelIndex)
	: Amulet("Amulet of Health", "Magical amulets. They were a gift for a pharaon. He had never worn them.", 0, 0, levelIndex, 'h'), m_maxHeath(maxHealth)
{
}

void HealthAmulet::applyAmuletEffect(Entity& target)
{
	if (m_maxHeath > 0) {
		m_healthModifier = std::make_shared<HealthModifier>(m_maxHeath);
		target.addModifier(m_healthModifier);
	}
}

void HealthAmulet::removeAmuletEffect(Entity& target)
{
	if (m_healthModifier != nullptr) {
		target.removeModifier(m_healthModifier);
	}
}


