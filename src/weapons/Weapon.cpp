#include "weapons/Weapon.hpp"
#include "entities/Entity.hpp"
#include "items/Bullet.hpp"
#include <stdexcept>
#include <utility>
#include <random>
#include <dice/DiceRoll.hpp>

Weapon::Weapon(std::string name, int magazineSize)
    : name(std::move(name)), magazineSize(magazineSize)
{
}

void Weapon::addBullet(Bullet &bullet) {
    if (magazine.size() < magazineSize) {
        magazine.push_back(std::make_shared<Bullet>(bullet));
    } else {
        throw std::runtime_error("Magazine is full");
    }
}

// Damage will be calculated in Character class (bad design)
void Weapon::shoot() {
    if (magazine.empty()) {
        throw std::runtime_error("No bullets in the magazine!");
    }

    magazine.pop_back();
}

int Weapon::getAmmo() {
    return static_cast<int>(magazine.size());
}

int Weapon::getMagazineSize() const {
    return magazineSize;
}

std::vector<std::shared_ptr<Bullet>>& Weapon::getMagazine() {
    return magazine;
}

std::string& Weapon::getName() {
    return name;
}