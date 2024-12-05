#include "entities/Phantom.hpp"
#include "effects/FearEffect.hpp"

Phantom::Phantom(const std::string &name, int attackRange, float attackDamage, float health, float defense,
                 float priority, float dodgeChance, int x, int y, char symbol)
                 : Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void Phantom::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 8);
            int diceRoll = dis(gen);

            float physicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            float magicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);

            diceRoll = dis(gen);
            if (diceRoll <= 4) {
                auto fearEffect = std::make_shared<FearEffect>(3, 1.5f);
                target.applyEffects(fearEffect);
            }
        }
        resetCooldown(this->getPriority());
    } else {
        throw std::runtime_error("Pharaon's phantom is on cooldown");
    }
}

void Phantom::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - (physicalDamage * 0.1f) - (magicalDamage));
}

void Phantom::heal(float amount) {
    health = std::min(maxHealth, health + amount);
}

void Phantom::move(int dx, int dy) {}

void Phantom::update() {
    Entity::update();
}

std::shared_ptr<Entity> Phantom::clone() const {
    return std::make_shared<Phantom>(*this);
}
