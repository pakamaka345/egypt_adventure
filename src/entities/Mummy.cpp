#include "entities/Mummy.hpp"
#include "dice/DiceRoll.hpp"
#include "Map.hpp"

Mummy::Mummy(const std::string &name, int attackRange, float attackDamage, float health, float defense, float priority,
             float dodgeChance, int x, int y, char symbol)
             : Entity(name, attackRange, attackDamage, health, defense, priority, dodgeChance, x, y, symbol)
{
}

void Mummy::attack(Entity &target) {
    if (isReady()) {
        if (canAttack(target)) {
            DiceRoll dice(8);
            int diceRoll = dice.roll();

            float physicalDamage = (attackDamage * float(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            float magicalDamage = ((attackDamage * 0.3f) * float(diceRoll) / 4.0f) * (1.0f - target.getDefense());
            target.takeDamage(physicalDamage, magicalDamage);
        }
        resetCooldown(this->getPriority());
    } else {
        throw std::runtime_error("Mummy is on cooldown");
    }
}

void Mummy::takeDamage(float physicalDamage, float magicalDamage) {
    health = std::max(0.0f, (health - (physicalDamage * 0.7f) - magicalDamage));

    if (health/maxHealth < 0.3) {
        setAttackDamage(getAttackDamage() * 1.2f);
        setDefense(getDefense() * 1.1f);
    }
}

void Mummy::heal(float amount) {
    health = std::min(maxHealth, (health + amount));
}

void Mummy::move(int dx, int dy) {
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}

void Mummy::update() {
    Entity::update();
    regenerate();
}

void Mummy::summonMinions(Map &map) {
    auto pos = map.getFreePositionsAround(this->getX(), this->getY(), 1, 2);
    if (pos.empty()) {
        return;
    }

    for (auto& p : pos) {
        std::shared_ptr<Entity> minion = std::make_shared<Mummy>("Mummy Minion", 1, 5.0f, 10.0f, 0.1f, 0.5f, 0.1f, p.first, p.second, 'm');
        map.placeEntity(p.first, p.second, minion);
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

