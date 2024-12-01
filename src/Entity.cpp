#include "entities/Entity.hpp"


Entity::Entity(const std::string& name, int attackRange,  float attackDamage, float health, float defense, float priority,
               float dodgeChance, int x, int y, char symbol)
               : name(name), attackRange(attackRange), attackDamage(attackDamage), health(health), maxHealth(health), defense(defense), priority(priority), cooldown(0),
               dodgeChance(dodgeChance), activeAmulets(), GameObject(x, y, symbol)
{
}

void Entity::addAmulet(const std::shared_ptr<Amulet>& amulet) {
    amulet->use(*this);
    activeAmulets.push_back(amulet);
}

void Entity::removeAmulet(const std::shared_ptr<Amulet>& amulet) {
    if (std::find(activeAmulets.begin(), activeAmulets.end(), amulet) == activeAmulets.end())
        throw std::invalid_argument("Amulet not found in active amulets");

    amulet->deactivate(*this);
    activeAmulets.erase(
            std::remove(activeAmulets.begin(), activeAmulets.end(), amulet),
            activeAmulets.end()
            );
}

bool Entity::canBePlacedOn(TileType::Type tileType) const {
    return tileType == TileType::Type::FLOOR;
}

bool Entity::isAlive() const {
    return health > 0;
}

bool Entity::canAttack(Entity &target) const {
    int radius = 0;

    if (posX == target.getX())
        radius = std::abs(posY - target.getY());
    else if (posY == target.getY())
        radius = std::abs(posX - target.getX());
    else
        return false;

    return radius <= attackRange;
}

std::string &Entity::getName() {
    return name;
}

float Entity::getHealth() const {
    return health;
}

float Entity::getMaxHealth() const {
    return maxHealth;
}

int Entity::getAttackRange() const {
    return attackRange;
}

float Entity::getAttackDamage() const {
    return attackDamage;
}

float Entity::getDefense() const {
    return defense;
}

float Entity::getPriority() const {
    return priority;
}

int Entity::getCooldown() const {
    return cooldown;
}

float Entity::getDodgeChance() const {
    return dodgeChance;
}


