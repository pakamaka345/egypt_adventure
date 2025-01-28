#include "entities/Skeleton.hpp"
#include <states/GameState.hpp>
#include <utils/EventManager.hpp>
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
            eventManager.addEvent(EventType::Combat,
                getName() + " attacks " + target.getName() + " for " + std::to_string(physicalDamage) + " physical damage and " + std::to_string(magicalDamage) + " magical damage"
                );

            eventManager.addEvent(EventType::Combat,
                getName() + " kicked himself for " + std::to_string(0.1f * getHealth()) + " damage due to the attack"
                );
        }
    }  else {
        eventManager.addEvent(EventType::Combat, getName() + " is still on cooldown");
    }
}

void Skeleton::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - physicalDamage - (magicalDamage * 0.7f));

    eventManager.addEvent(EventType::Combat,
        getName() + " takes " + std::to_string(physicalDamage) + " physical damage" +
        " and " + std::to_string(magicalDamage * 0.7) + " magical damage" +
        " left with " + std::to_string(health) + " hp"
        );

    if (health == 0 && resurrection > 0) {
        health = 0.5f * getMaxHealth();
        resurrection--;

        eventManager.addEvent(EventType::Combat, getName() + " resurrected with 50% health");
    }
}

void Skeleton::heal(float amount) {
    health = std::max(0.0f, health + (amount * -1.0f));

    eventManager.addEvent(EventType::Combat,
        getName() + " tries to heal himself for " + std::to_string(amount) + " but he is skeleton so he takes damage"
        );
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

    eventManager.addEvent(EventType::Combat, getName() + " dies");

    chanceToDropGrenades(7, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropAmulets(5, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropPotions(3, DiceRoll(), gameState.getLevels()[getZ()], getZ());
}


std::shared_ptr<Entity> Skeleton::clone() const {
    return std::make_shared<Skeleton>(*this);
}