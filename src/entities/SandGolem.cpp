#include "entities/SandGolem.hpp"

#include <ai/SandGolemAIComponent.hpp>
#include "utils/EventManager.hpp"
#include "dice/DiceRoll.hpp"
#include "effects/EffectManager.hpp"
#include "effects/Effect.hpp"
#include "effects/SandShield.hpp"
#include "map/Map.hpp"
#include "tiles/Tile.hpp"
#include "tiles/SandTile.hpp"
#include "states/GameState.hpp"

SandGolem::SandGolem(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense, float priority,
             float dodgeChance, int x, int y, int z, char symbol)
        : maxShieldHealth(0), shieldHealth(0),
        Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, z, symbol)
{
    aiComponent = std::make_shared<SandGolemAIComponent>();
}

void SandGolem::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();

            float physicalDamage = (getPhysicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            float magicalDamage = (getMagicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);
            resetCooldown(this->getPriority());
            eventManager.addEvent(EventType::Combat,
                getName() + " attacks " + target.getName() + " for " + std::to_string(physicalDamage) + " physical damage and " + std::to_string(magicalDamage) + " magical damage"
                );
        }
    } else {
        eventManager.addEvent(EventType::Combat, getName() + " is still on cooldown");
    }
}

void SandGolem::takeDamage(float physicalDamage, float magicalDamage) {
    if (shieldHealth > 0) {
        shieldHealth = std::max(0.0f, shieldHealth - physicalDamage - magicalDamage);
        eventManager.addEvent(EventType::Combat, getName() + " shield absorbs " + std::to_string(physicalDamage) + " physical damage and " + std::to_string(magicalDamage) + " magical damage. Shield health left: " + std::to_string(shieldHealth));
        return;
    }
    health = std::max(0.0f, health - physicalDamage - magicalDamage);
    eventManager.addEvent(EventType::Combat,
        getName() + " takes " + std::to_string(physicalDamage) + " physical damage" +
        " and " + std::to_string(magicalDamage) + " magical damage" +
        " left with " + std::to_string(health) + " hp"
        );

}

void SandGolem::heal(float amount) {
    health = std::min(getMaxHealth(), health + amount);
    eventManager.addEvent(EventType::Combat, getName() + " heals for " + std::to_string(amount) + " hp");
}

void SandGolem::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void SandGolem::update(GameState& gameState) {
    Entity::update(gameState);

    //auto map = GameState::getInstance().getCurrentLevel().getMap();
    healOnSand(*gameState.getLevels()[getZ()]->getMap());
}

void SandGolem::onDeath(GameState& gameState)
{
    Entity::onDeath(gameState);

    eventManager.addEvent(EventType::Combat, getName() + " dies");

    chanceToDropGrenades(6, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropAmulets(6, DiceRoll(), gameState.getLevels()[getZ()], getZ());
    chanceToDropPotions(4, DiceRoll(), gameState.getLevels()[getZ()], getZ());
}


std::shared_ptr<Entity> SandGolem::clone() const {
    return std::make_shared<SandGolem>(*this);
}

void SandGolem::activateSandShield() {
    for (auto& effect : effectManager.getActiveEffects()) {
        if (effect->getName() == "sand shield") {
            return;
        }
    }

    eventManager.addEvent(EventType::Combat, getName() + " activates Sand Shield");

    this->applyEffects(std::make_shared<SandShield>(10, 100));
}

void SandGolem::coverWithSand(Map &map, int radius) {
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            int newX = getX() + dx;
            int newY = getY() + dy;
            if (map.isInsideMap(newX, newY)) {
                DiceRoll dice(100);
                int diceRoll = dice.roll();
                if (diceRoll < 40) {
                    if (map.getTile(newX, newY)->getTileType() == TileType::FLOOR) {
                        std::shared_ptr<Tile> sandTile = std::make_shared<SandTile>(newX, newY, getZ());
                        sandTile->setEntity(map.getTile(newX, newY)->getEntity());
                        sandTile->addItems(map.getTile(newX, newY)->getItems());
                        map.setTile(sandTile);
                    }
                }
            }
        }
    }
}

void SandGolem::healOnSand(Map &map) {
    if (map.getTile(this->getX(), this->getY())->getTileType() == TileType::SAND) {
        sandTimer++;
        if (sandTimer >= 2) {
            float shieldAmount = DiceRoll().randomNumber(5, 15);
            shieldHealth = std::min(maxShieldHealth, shieldHealth + shieldAmount);
            eventManager.addEvent(EventType::Combat, getName() + " heals for " + std::to_string(shieldAmount) + " shield health. Current shield health: " + std::to_string(shieldHealth));
            sandTimer = 0;
        }
    }
}

void SandGolem::setShieldHealth(float shieldHealth) {
    this->maxShieldHealth = shieldHealth;
    this->shieldHealth = shieldHealth;
}

float SandGolem::getShieldHealth() const {
    return shieldHealth;
}

float SandGolem::getShieldMaxHealth() const
{
    return maxShieldHealth;
}
