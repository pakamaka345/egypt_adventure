#include "entities/SandGolem.hpp"
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
}

void SandGolem::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();

            float physicalDamage = (getPhysicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            float magicalDamage = (getMagicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);
        }
        resetCooldown(this->getPriority());
    } else {
        throw std::runtime_error("Sand golem is on cooldown");
    }
}

void SandGolem::takeDamage(float physicalDamage, float magicalDamage) {
    if (shieldHealth > 0) {
        shieldHealth = std::max(0.0f, shieldHealth - physicalDamage - magicalDamage);
        return;
    }
    health = std::max(0.0f, health - physicalDamage - magicalDamage);
}

void SandGolem::heal(float amount) {
    health = std::min(getMaxHealth(), health + amount);
}

void SandGolem::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void SandGolem::update(GameState& gameState) {
    Entity::update(gameState);

    //auto map = GameState::getInstance().getCurrentLevel().getMap();
    healOnSand(*gameState.getCurrentLevel().getMap());
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

    this->applyEffects(std::make_shared<SandShield>(3, 50));
}

void SandGolem::coverWithSand(Map &map, int radius) {
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            int newX = getX() + dx;
            int newY = getY() + dy;
            if (map.isInsideMap(newX, newY)) {
                DiceRoll dice(100);
                int diceRoll = dice.roll();
                if (diceRoll < 70) {
                    if (map.getTile(newX, newY)->getTileType() == TileType::FLOOR) {
                        std::shared_ptr<Tile> sandTile = std::make_shared<SandTile>(newX, newY, getZ());
                        map.setTile(sandTile);
                    }
                }
            }
        }
    }
}

void SandGolem::healOnSand(Map &map) {
    static int sandTimer = 0;
    if (map.getTile(this->getX(), this->getY())->getTileType() == TileType::SAND) {
        sandTimer++;
        if (sandTimer >= 3) {
            shieldHealth = std::min(maxShieldHealth, shieldHealth + 15.0f);
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
