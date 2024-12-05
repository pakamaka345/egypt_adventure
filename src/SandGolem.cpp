#include "entities/SandGolem.hpp"

SandGolem::SandGolem(const std::string &name, int attackRange, float attackDamage, float health, float defense, float priority,
             float dodgeChance, int x, int y, char symbol)
        : Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void SandGolem::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 8);
            int diceRoll = dis(gen);

            float physicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            float magicalDamage = (attackDamage * float(diceRoll) / 8.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);
        }
        resetCooldown(this->getPriority());
    } else {
        throw std::runtime_error("Sand golem is on cooldown");
    }
}

void SandGolem::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - physicalDamage - magicalDamage);
}

void SandGolem::heal(float amount) {
    health = std::min(maxHealth, health + amount);
}

void SandGolem::move(int dx, int dy) {

}

void SandGolem::update() {
    Entity::update();
}

std::shared_ptr<Entity> SandGolem::clone() const {
    return std::make_shared<SandGolem>(*this);
}
