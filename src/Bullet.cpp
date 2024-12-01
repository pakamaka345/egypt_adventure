#include "items/Bullet.hpp"
#include "entities/Character.hpp"

Bullet::Bullet(float physicalDamage, float magicalDamage,
               const std::string &name, const std::string &description, int x, int y, char symbol)
        : physicalDamage(physicalDamage), magicalDamage(magicalDamage), Item(name, description, x, y, symbol)
{
}

void Bullet::use(Entity &target) {
    try {
        auto& character = dynamic_cast<Character&>(target);
        character.getRevolver()->addBullet(*this);
    } catch (const std::bad_cast& e) {
        throw std::runtime_error("Cannot use bullet on non-character entity");
    }
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