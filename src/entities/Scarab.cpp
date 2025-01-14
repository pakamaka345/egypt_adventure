#include "entities/Scarab.hpp"

#include <effects/GroupAttackBonus.hpp>
#include <map/Map.hpp>

#include "dice/DiceRoll.hpp"

Scarab::Scarab(const std::string &name, int attackRange, float physicalDamage, float magicalDamage, float health, float defense,
               float priority, float dodgeChance, int x, int y, char symbol)
               : groupAttackBonus(1.0f),
               Entity(name, attackRange, physicalDamage, magicalDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void Scarab::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();
            float physicalDamage = (getPhysicalDamage() * float(diceRoll) / 4.0f) * (1.0f - target.getDefense()) * groupAttackBonus;
            target.takeDamage(physicalDamage, getMagicalDamage());
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
    health = std::min(getMaxHealth(), (health + amount));
}

void Scarab::move(int dx, int dy) {
    Entity::move(dx, dy);
}

void Scarab::update(Map& map) {
    Entity::update(map);

    findNearestScarabs(map);
}

void Scarab::findNearestScarabs(Map& map)
{
    std::vector<std::shared_ptr<Scarab>> scarabs;
    for (int dx = getX() - 1; dx <= getX() + 1; dx++) {
        for (int dy = getY() - 1; dy <= getY() + 1; dy++) {
            if (dx == getX() && dy == getY()) continue;
            if (map.isInsideMap(dx, dy)) {
                auto scarab = std::dynamic_pointer_cast<Scarab>(map.getEntityAt(dx, dy));
                if (scarab) {
                    scarabs.push_back(scarab);
                }
            }
        }
    }

    for (int i = 0; i < scarabs.size(); i++) {
        this->applyEffects(std::make_shared<GroupAttackBonus>(1, 1.1f));
    }
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

