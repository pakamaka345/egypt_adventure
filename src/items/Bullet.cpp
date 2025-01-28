#include "items/Bullet.hpp"
#include "entities/Character.hpp"
#include "weapons/Weapon.hpp"

Bullet::Bullet(float physicalDamage, float magicalDamage, int levelIndex)
        : physicalDamage(physicalDamage), magicalDamage(magicalDamage), Item("bullet", "Simple bullets for Piter`s revolver.", 0, 0, levelIndex, 'b')
{
}

void Bullet::use(Entity &target) {

    auto* character = dynamic_cast<Character*>(&target);
    if (!character) {
        throw std::invalid_argument("Target must be a Character to use a bullet.");
    }
    character->getRevolver()->addBullet(*this);
}

void Bullet::increasePhysicalDamage(float value) {
    physicalDamage += value;
}

void Bullet::increaseMagicalDamage(float value) {
    magicalDamage += value;
}

void Bullet::decreasePhysicalDamage(float value) {
    physicalDamage -= value;
}

void Bullet::decreaseMagicalDamage(float value) {
    magicalDamage -= value;
}

std::string Bullet::getSpecifications()
{
    std::string specs = "Physical damage: " + std::to_string(physicalDamage) + "\n";
    specs += "Magical damage: " + std::to_string(magicalDamage) + "\n";
    return specs;
}
