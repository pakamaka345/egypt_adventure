#include "entities/Mummy.hpp"

Mummy::Mummy(const std::string &name, int attackRange, float attackDamage, float health, float defense, float priority,
             float dodgeChance, int x, int y, char symbol)
             : Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void Mummy::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 8);
            int diceRoll = dis(gen);

            float physicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            float magicalDamage = ((attackDamage * 0.3f) * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);
        }
        resetCooldown(this->getPriority());
    } else {
        throw std::runtime_error("Mummy is on cooldown");
    }
}

void Mummy::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - (physicalDamage * 0.7f) - magicalDamage));

    if (health/maxHealth < 0.3) {
        setAttackDamage(getAttackDamage() * 1.5f);
        setDefense(getDefense() * 1.2f);
    }
}

void Mummy::heal(float amount) {
    health = std::min(maxHealth, (health + amount));
}

void Mummy::move(int dx, int dy) {}

void Mummy::update() {
    Entity::update();
    regenerate();
}

void Mummy::regenerate() {
    heal(1.0f);
}

std::shared_ptr<Entity> Mummy::clone() const {
    return std::make_shared<Mummy>(*this);
}

