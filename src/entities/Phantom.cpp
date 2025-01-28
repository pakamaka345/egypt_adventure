#include "entities/Phantom.hpp"

#include <states/GameState.hpp>
#include <utils/EventManager.hpp>
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

                eventManager.addEvent(EventType::Combat,
                    getName() + " inflicted fear on " + target.getName() + " for 3 turns"
                    );
            }
            resetCooldown(this->getPriority());
            eventManager.addEvent(EventType::Combat,
                getName() + " attacks " + target.getName() + " for " + std::to_string(physicalDamage) + " physical damage and " + std::to_string(magicalDamage) + " magical damage"
                );
        }
    } else {
        eventManager.addEvent(EventType::Combat, getName() + " is still on cooldown");
    }
}

void Phantom::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, health - (physicalDamage * 0.1f) - (magicalDamage * 1.3f));

    eventManager.addEvent(EventType::Combat,
        getName() + " takes " + std::to_string(physicalDamage * 0.1) + " physical damage" +
        " and " + std::to_string(magicalDamage * 1.3) + " magical damage" +
        " left with " + std::to_string(health) + " hp"
        );
}

void Phantom::heal(float amount) {
    health = std::min(getMaxHealth(), health + amount);

    auto& eventManager = EventManager::getInstance();
    eventManager.addEvent(EventType::Combat, getName() + " heals for " + std::to_string(amount) + " hp");
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

    eventManager.addEvent(EventType::Combat, getName() + " dies");

    chanceToDropAmulets(7, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropPotions(4, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropGrenades(8, DiceRoll(), gameState.getLevels()[getZ()], getZ());
}


std::shared_ptr<Entity> Phantom::clone() const {
    return std::make_shared<Phantom>(*this);
}
