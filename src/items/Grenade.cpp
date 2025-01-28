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

std::string Grenade::getSpecifications()
{
	std::string specs = "Physical Damage: " + std::to_string(m_physicalDamage) + "\nMagical Damage: " + std::to_string(m_magicalDamage) + "\n";
	specs += "Radius: " + std::to_string(getRadius()) + "\n";
	return specs;
}
