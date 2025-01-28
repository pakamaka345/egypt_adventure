#include "weapons/Weapon.hpp"
#include "entities/Entity.hpp"
#include "items/Bullet.hpp"
#include <stdexcept>
#include <utility>
#include <random>
#include <dice/DiceRoll.hpp>

Weapon::Weapon(std::string name, int magazineSize)
    : name(std::move(name)), magazineSize(magazineSize), eventManager(EventManager::getInstance())
{
}

void Weapon::addBullet(Bullet &bullet) {
    if (magazine.size() < magazineSize) {
        magazine.push_back(std::make_shared<Bullet>(bullet));
    } else {
        eventManager.addEvent(EventType::System, "Magazine is full!");
    }
}

// Damage will be calculated in Character class (bad design)
void Weapon::shoot() {
    if (magazine.empty()) {
        eventManager.addEvent(EventType::System, "Magazine is empty!");
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