#include "entities/Scarab.hpp"

Scarab::Scarab(const std::string &name, int attackRange, float attackDamage, float health, float defense,
               float priority, float dodgeChance, int x, int y, char symbol)
               : Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void Scarab::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 8);
            int diceRoll = dis(gen);
            float physicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, 0);
        }
        resetCooldown(this->getPriority());
    } else {
        throw std::runtime_error("Scarab is on cooldown");
    }
}

void Scarab::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - physicalDamage - magicalDamage));
}

void Scarab::heal(float amount) {
    health = std::min(maxHealth, (health + amount));
}

void Scarab::move(int dx, int dy) {
    //TODO: Implement movement
}

void Scarab::update() {
    Entity::update();
}

std::shared_ptr<Entity> Scarab::clone() const {
    return std::make_shared<Scarab>(*this);
}

