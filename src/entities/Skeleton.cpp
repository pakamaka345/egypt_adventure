#include "entities/Skeleton.hpp"
#include "dice/DiceRoll.hpp"

Skeleton::Skeleton(const std::string &name, int attackRange, float attackDamage, float health, float defense, float priority,
                   float dodgeChance, int x, int y, char symbol)
        : resurrection(1),
        Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

/**
 * @brief will throw a bone at the target so after the attack the skeleton will be damaged
 * @param target
 */
void Skeleton::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();

            int distance = distanceTo(target);
            float physicalDamage = 0.0f;
            if (distance != -1) {
                if (distance > 2) {
                    physicalDamage = (attackDamage * float(diceRoll) / 4.0f) * (1.0f - target.getDefense());
                } else {
                    physicalDamage = (attackDamage * float(diceRoll) / 4.0f) * (1.0f - target.getDefense()) * 0.5f;
                }

                target.takeDamage(physicalDamage, 0);
                this->takeDamage(0.1f * getHealth(), 0);
            }
        }

        resetCooldown(this->getPriority());
    }  else {
        throw std::runtime_error("Skeleton is on cooldown");
    }
}

void Skeleton::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - physicalDamage - (magicalDamage * 0.7f));

    if (health == 0 && resurrection > 0) {
        health = 0.5f * getMaxHealth();
        resurrection--;
    }
}

void Skeleton::heal(float amount) {
    health = std::max(0.0f, health + (amount * -1.0f));
}

void Skeleton::move(int dx, int dy) {
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Skeleton::update() {
    Entity::update();
}

std::shared_ptr<Entity> Skeleton::clone() const {
    return std::make_shared<Skeleton>(*this);
}

int Skeleton::distanceTo(Entity &target) const {
    if (target.getX() == this->getX()) {
        return std::abs(target.getY() - this->getY());
    } else if (target.getY() == this->getY()) {
        return std::abs(target.getX() - this->getX());
    }
    return -1;
}