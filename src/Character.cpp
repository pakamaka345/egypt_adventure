#include "entities/Character.hpp"

Character::Character(std::string &name, int x, int y, char symbol)
    : revolver(std::make_shared<Weapon>("Revolver", 6))
    , inventory()
    , Entity(name, 5, 10.0f, 50.0f, 0.3f, 5.0f, 0.2f, x, y, symbol)
{
}

void Character::reloadRevolver() {
    try {
        for (auto& amulet : activeAmulets) {
            amulet->deactivate(*this);
        }

        while (revolver->getAmmo() <= revolver->getMagazineSize() && inventory.hasItem("bullet")) {
            inventory.useItemWithRemoving("bullet", *this);
        }

        for (auto& amulet : activeAmulets) {
            amulet->use(*this);
        }
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("No bullets in inventory");
    }
}

void Character::addToInventory(const std::shared_ptr<Item> &item) {
    inventory.addItem(item);
}

void Character::removeFromInventory(const std::string &itemName) {
    inventory.removeItem(itemName);
}

void Character::attack(Entity &target) {
    if (revolver->getAmmo() > 0) {
        this->attackRange = 5.0f;
        if (canAttack(target)) {
            revolver->shoot(target);
        }
    } else {
        this->attackRange = 1.0f;
        if (canAttack(target)) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 8);

            int diceRoll = dis(gen);
            float physicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1 - target.getDefense());

            target.takeDamage(physicalDamage, 0);
        }

        throw std::runtime_error("No ammo in revolver");
    }
}

void Character::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - physicalDamage - magicalDamage));
}

void Character::heal(float amount) {
    health = std::min(maxHealth, (health + amount));
}

std::shared_ptr<Weapon> Character::getRevolver() {
    return revolver;
}