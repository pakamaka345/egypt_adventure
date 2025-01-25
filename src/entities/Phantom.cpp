#include "entities/Phantom.hpp"

#include <states/GameState.hpp>

#include "effects/FearEffect.hpp"
#include "dice/DiceRoll.hpp"
#include "ai/AIComponent.hpp"

Phantom::Phantom(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense,
                 float priority, float dodgeChance, int x, int y, int z, char symbol)
                 : Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, z, symbol)
{
    aiComponent = std::make_shared<AIComponent>();
}

void Phantom::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();

            float physicalDamage = (getPhysicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            float magicalDamage = (getMagicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);

            diceRoll = dice.roll();
            if (diceRoll <= 2) {
                auto fearEffect = std::make_shared<FearEffect>(3, 1.5f);
                target.applyEffects(fearEffect);
            }
            resetCooldown(this->getPriority());
        }
    } else {
        throw std::runtime_error("Pharaon's phantom is on cooldown");
    }
}

void Phantom::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - (physicalDamage * 0.1f) - (magicalDamage * 1.3f));
}

void Phantom::heal(float amount) {
    health = std::min(getMaxHealth(), health + amount);
}

void Phantom::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void Phantom::update(GameState& gameState) {
    Entity::update(gameState);
}

void Phantom::onDeath(GameState& gameState)
{
    Entity::onDeath(gameState);

    chanceToDropAmulets(5, DiceRoll(), gameState.getLevels()[getZ()], 2);
    chanceToDropAmulets(7, DiceRoll(), gameState.getLevels()[getZ()], 3);
    chanceToDropPotions(2, DiceRoll(), gameState.getLevels()[getZ()], 2);
    chanceToDropPotions(5, DiceRoll(), gameState.getLevels()[getZ()], 3);
    chanceToDropGrenades(6, DiceRoll(), gameState.getLevels()[getZ()], 2);
    chanceToDropGrenades(8, DiceRoll(), gameState.getLevels()[getZ()], 3);
}


std::shared_ptr<Entity> Phantom::clone() const {
    return std::make_shared<Phantom>(*this);
}
