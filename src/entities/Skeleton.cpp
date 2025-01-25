#include "entities/Skeleton.hpp"

#include <states/GameState.hpp>

#include "dice/DiceRoll.hpp"
#include "ai/AIComponent.hpp"

Skeleton::Skeleton(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense, float priority,
                   float dodgeChance, int x, int y, int z, char symbol)
        : resurrection(1),
        Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, z, symbol)
{
    aiComponent = std::make_shared<AIComponent>();
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

            const int distance = distanceTo(target);
            float physicalDamage = 0.0f;
            if (distance > 1) {
                physicalDamage = (getPhysicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            } else {
                physicalDamage = (getPhysicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense()) * 0.5f;
            }

            target.takeDamage(physicalDamage, getMagicalDamage());
            this->takeDamage(0.1f * getHealth(), 0);
            resetCooldown(this->getPriority());
        }
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
    Entity::move(dx, dy);
}

void Skeleton::update(GameState& gameState) {
    Entity::update(gameState);
}

void Skeleton::onDeath(GameState& gameState)
{
    Entity::onDeath(gameState);

    chanceToDropGrenades(6, DiceRoll(), gameState.getLevels()[getZ()], 1);
    chanceToDropAmulets(5, DiceRoll(), gameState.getLevels()[getZ()], 1);
    chanceToDropGrenades(8, DiceRoll(), gameState.getLevels()[getZ()], 2);
    chanceToDropPotions(3, DiceRoll(), gameState.getLevels()[getZ()], 1);
}


std::shared_ptr<Entity> Skeleton::clone() const {
    return std::make_shared<Skeleton>(*this);
}