#include "entities/Mummy.hpp"
#include "dice/DiceRoll.hpp"
#include "map/Map.hpp"
#include "modifiers/DefenseModifier.hpp"
#include "modifiers/PhysicalDamageModifier.hpp"

Mummy::Mummy(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense, float priority,
             float dodgeChance, int x, int y, int z, char symbol)
             : Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, z, symbol)
{
}

void Mummy::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();

            float physicalDamage = (getPhysicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            float magicalDamage = (getMagicalDamage() * static_cast<float>(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);
            resetCooldown(this->getPriority());
        }
    } else {
        throw std::runtime_error("Mummy is on cooldown");
    }
}

void Mummy::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - (physicalDamage * 0.7f) - magicalDamage));

    if (health/maxHealth < 0.3) {
        addModifier(std::make_shared<PhysicalDamageModifier>(physicalDamage * 1.2f));
        addModifier(std::make_shared<DefenseModifier>(defense * 1.3f));
    }
}

void Mummy::heal(float amount) {
    health = std::min(getMaxHealth(), (health + amount));
}

void Mummy::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void Mummy::update(GameState& gameState) {
    Entity::update(gameState);
    regenerate();
}

void Mummy::summonMinions(Map &map) const {
    auto pos = map.getFreePositionsAround(this->getX(), this->getY(), 1, 2);
    if (pos.empty()) {
        return;
    }

    for (auto& p : pos) {
        std::shared_ptr<Entity> minion = std::make_shared<Mummy>("Mummy Minion", 1, 5.0f, 0.0f, 10.0f, 0.1f, 0.5f, 0.1f, p.x, p.y, getZ(), 'm');
        map.placeEntity(p.x, p.y, minion);
    }
}

void Mummy::regenerate() {
    if (health > 0.0f) {
        heal(1.0f);
    }
}

std::shared_ptr<Entity> Mummy::clone() const {
    return std::make_shared<Mummy>(*this);
}

