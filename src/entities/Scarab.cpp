#include "entities/Scarab.hpp"
#include <effects/GroupAttackBonus.hpp>
#include <states/GameState.hpp>
#include <map/Map.hpp>
#include <ai/AIComponent.hpp>
#include <dice/DiceRoll.hpp>
#include <utils/EventManager.hpp>

Scarab::Scarab(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense,
               float priority, float dodgeChance, int x, int y, int z, char symbol)
               : groupAttackBonus(1.0f),
               Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, z, symbol)
{
    aiComponent = std::make_shared<AIComponent>();
}

void Scarab::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();
            float physicalDamage = (getPhysicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense()) * groupAttackBonus;
            target.takeDamage(physicalDamage, getMagicalDamage());
            resetCooldown(this->getPriority());
            eventManager.addEvent(EventType::Combat,
                getName() + " attacks " + target.getName() + " for " + std::to_string(physicalDamage) + " physical damage and " + std::to_string(magicalDamage) + " magical damage"
                );
        }
    } else {
        eventManager.addEvent(EventType::Combat, getName() + " is still on cooldown");
    }
}

void Scarab::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - physicalDamage - magicalDamage));

    eventManager.addEvent(EventType::Combat,
        getName() + " takes " + std::to_string(physicalDamage) + " physical damage" +
        " and " + std::to_string(magicalDamage) + " magical damage" +
        " left with " + std::to_string(health) + " hp"
        );
}

void Scarab::heal(float amount) {
    health = std::min(getMaxHealth(), (health + amount));
    eventManager.addEvent(EventType::Combat, getName() + " heals for " + std::to_string(amount) + " hp");
}

void Scarab::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void Scarab::update(GameState& gameState) {
    Entity::update(gameState);

    findNearestScarabs(*gameState.getCurrentLevel().getMap());
}

void Scarab::findNearestScarabs(const Map& map)
{
    std::vector<std::shared_ptr<Scarab>> scarabs;
    for (int dx = getX() - 1; dx <= getX() + 1; dx++) {
        for (int dy = getY() - 1; dy <= getY() + 1; dy++) {
            if (dx == getX() && dy == getY()) continue;
            if (map.isInsideMap(dx, dy)) {
                if (auto scarab = std::dynamic_pointer_cast<Scarab>(map.getEntityAt(dx, dy))) {
                    scarabs.push_back(scarab);
                }
            }
        }
    }

    for (int i = 0; i < scarabs.size(); i++) {
        this->applyEffects(std::make_shared<GroupAttackBonus>(1, 0.1f));
    }

    if (!scarabs.empty()) {
        eventManager.addEvent(EventType::Combat, getName() + " is now in a group with " + std::to_string(scarabs.size()) + " other scarabs. Damage increased by " + std::to_string(groupAttackBonus));
    }
}

void Scarab::onDeath(GameState& gameState)
{
    Entity::onDeath(gameState);

    eventManager.addEvent(EventType::Combat, getName() + " dies");

    chanceToDropAmulets(8, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropPotions(4, DiceRoll(), gameState.getLevels()[getZ()], getZ());
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

