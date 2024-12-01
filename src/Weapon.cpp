#include "weapons/Weapon.hpp"
#include <stdexcept>
#include <utility>

Weapon::Weapon(std::string name, int magazineSize)
    : name(std::move(name)), magazine(), magazineSize(magazineSize)
{
}

void Weapon::addBullet(Bullet &bullet) {
    if (magazine.size() < magazineSize) {
        magazine.push_back(bullet);
    } else {
        throw std::runtime_error("Magazine is full");
    }
}

void Weapon::shoot(Entity &target) {
    if (magazine.empty()) {
        throw std::runtime_error("No bullets in the magazine!");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 8);

    Bullet bullet = magazine.back();
    magazine.pop_back();

    int diceRoll = dis(gen);

    float physicalDamage = (bullet.getPhysicalDamage() * float(diceRoll) / 8.0f) * (1 - target.getDefense());
    float magicalDamage = (bullet.getMagicalDamage() * float(diceRoll) / 8.0f) * (1 - target.getDefense());
    target.takeDamage(physicalDamage, magicalDamage);
}

void Weapon::shootWithMiss() {
    if (magazine.empty()) {
        throw std::runtime_error("No bullets in the magazine!");
    }

    magazine.pop_back();
}