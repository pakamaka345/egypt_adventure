#include "entities/Skeleton.hpp"

Skeleton::Skeleton(const std::string &name, int attackRange, float attackDamage, float health, float defense, float priority,
                   float dodgeChance, int x, int y, char symbol)
        : Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

/**
 * @brief will throw a bone at the target so after the attack the skeleton will be damaged
 * @param target
 */
void Skeleton::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 8);
            int diceRoll = dis(gen);

            float physicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, 0);
            float currentHealth = getHealth();
            float damage = 0.1f * currentHealth;
            this->takeDamage(damage, 0);
        }

        resetCooldown(this->getPriority());
    }  else {
        throw std::runtime_error("Skeleton is on cooldown");
    }
}

void Skeleton::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - physicalDamage - (magicalDamage * 0.5f));
}

void Skeleton::heal(float amount) {
    health = std::min(0.0f, health + (amount * -1.0f));
}

void Skeleton::move(int dx, int dy) {

}

void Skeleton::update() {
    Entity::update();
}

std::shared_ptr<Entity> Skeleton::clone() const {
    return std::make_shared<Skeleton>(*this);
}
