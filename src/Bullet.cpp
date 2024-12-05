#include "items/Bullet.hpp"
#include "entities/Character.hpp"
#include "weapons/Weapon.hpp"

Bullet::Bullet(float physicalDamage, float magicalDamage,
               const std::string &name, const std::string &description, int x, int y, char symbol)
        : physicalDamage(physicalDamage), magicalDamage(magicalDamage), Item(name, description, x, y, symbol)
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