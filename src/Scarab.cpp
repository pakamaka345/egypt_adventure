#include "entities/Scarab.hpp"
#include "dice/DiceRoll.hpp"

Scarab::Scarab(const std::string &name, int attackRange, float attackDamage, float health, float defense,
               float priority, float dodgeChance, int x, int y, char symbol)
               : groupAttackBonus(1.0f),
               Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void Scarab::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();
            float physicalDamage = (attackDamage * float(diceRoll) / 4.0f) * (1.0f - target.getDefense()) * groupAttackBonus;
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
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Scarab::update() {
    Entity::update();
}

std::shared_ptr<Entity> Scarab::clone() const {
    return std::make_shared<Scarab>(*this);
}

void Scarab::setGroupAttackBonus(float bonus) {
    groupAttackBonus = bonus;
}

float Scarab::getGroupAttackBonus() const {
    return groupAttackBonus;
}

