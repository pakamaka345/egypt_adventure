#include "entities/Entity.hpp"


Entity::Entity(std::string &name, float attackDamage, int health, float defense, float priority,
               float dodgeChance, int x, int y, char symbol)
               : name(name), attackDamage(attackDamage), health(health), defense(defense), priority(priority),
               dodgeChance(dodgeChance), activeAmulets(), GameObject(x, y, symbol)
{
}

bool Entity::isAlive() const {
    return health > 0;
}

std::string &Entity::getName() {
    return name;
}

int Entity::getHealth() const {
    return health;
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

float Entity::getDodgeChance() const {
    return dodgeChance;
}


