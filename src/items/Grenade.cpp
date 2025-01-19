//
// Created by pakamaka345 on 1/16/25.
//

#include "Grenade.hpp"
#include <entities/Entity.hpp>

Grenade::Grenade(float magicalDamage, float physicalDamage, int radius, int levelIndex)
	: m_magicalDamage(magicalDamage), m_physicalDamage(physicalDamage),
	ThrowableItem(radius, "grenade", "Fancy grenades are made by hand using nails.", 0, 0, levelIndex, 'g')

{
}

void Grenade::use(Entity& target)
{
	target.takeDamage(m_physicalDamage, m_magicalDamage);
}

