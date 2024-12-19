#include "entities/Character.hpp"
#include "weapons/Weapon.hpp"
#include "items/Bullet.hpp"
#include "items/amulets/Amulet.hpp"

Character::Character(const std::string &name, int x, int y, char symbol)
    : revolver(std::make_shared<Weapon>("Revolver", 6))
    , inventory()
    , Entity(name, 5, 10.0f, 50.0f, 0.3f, 2.0f, 0.2f, x, y, symbol)
{
}

void Character::reloadRevolver() {
    try {
        for (auto& amulet : activeAmulets) {
            amulet->removeAmuletEffect(*this);
        }

        while (revolver->getAmmo() < revolver->getMagazineSize() && inventory.hasItem("bullet")) {
            inventory.useItemWithRemoving("bullet", *this);
        }

        for (auto& amulet : activeAmulets) {
            amulet->applyAmuletEffect(*this);
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

void Character::useItemWithRemoving(const std::string &itemName, Entity &target) {
    inventory.useItemWithRemoving(itemName, target);
}

void Character::useItem(const std::string &itemName, Entity &target) {
    inventory.useItem(itemName, target);
}

void Character::attack(Entity &target) {
    if (isReady()) {
        if (revolver->getAmmo() > 0) {
            this->attackRange = 5.0f;
            if (canAttack(target)) {
                revolver->shoot(target);
            }
            revolver->shootWithMiss();
            resetCooldown(this->priority);
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

            resetCooldown(this->priority);
            throw std::runtime_error("No ammo in revolver");
        }
    } else {
        throw std::runtime_error("Character is on cooldown");
    }
}

void Character::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - physicalDamage - magicalDamage));
}

void Character::heal(float amount) {
    health = std::min(maxHealth, (health + amount));
}

void Character::move(int dx, int dy) {
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Character::update() {
    Entity::update();
}

std::shared_ptr<Entity> Character::clone() const {
    return std::make_shared<Character>(*this);
}

const Inventory &Character::getInventory() const {
    return inventory;
}

const std::shared_ptr<Weapon> &Character::getRevolver() const {
    return revolver;
}

