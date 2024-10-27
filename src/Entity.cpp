#include "Entity.hpp"

Entity::Entity(std::string name, int health, int strength, char symbol, int x, int y)
    : GameObject(x, y), name(name), health(health), strength(strength), symbol(symbol)
{
}

char Entity::getSymbol() const
{
    return symbol;
}

void Entity::setSymbol(char symbol)
{
    this->symbol = symbol;
}

std::string Entity::getName() const
{
    return name;
}

void Entity::setName(std::string name)
{
    this->name = name;
}

int Entity::getHealth() const
{
    return health;
}

void Entity::setHealth(int health)
{
    this->health = health;
}

int Entity::getStrength() const
{
    return strength;
}

void Entity::setStrength(int strength)
{
    this->strength = strength;
}

bool Entity::isAlive() const
{
    return health > 0;
}
