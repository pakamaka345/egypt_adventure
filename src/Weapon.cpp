#include "weapons/Weapon.hpp"

Weapon::Weapon(std::string& name, std::pair<float, float>& physicalDamage, std::pair<float, float>& magicalDamage)
    : name(name), physicalDamage(physicalDamage), magicalDamage(magicalDamage)
{
}

std::string& Weapon::getName()
{
    return name;
}

std::pair<float, float>& Weapon::getPhysicalDamage() {
    return physicalDamage;
}

std::pair<float, float>& Weapon::getMagicalDamage() {
    return magicalDamage;
}

void Weapon::increasePhysicalDamage(float value) {
    physicalDamage.first += value;
    physicalDamage.second += value;
}

void Weapon::increaseMagicalDamage(float value) {
    magicalDamage.first += value;
    magicalDamage.second += value;
}