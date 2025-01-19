#include "items/ThrowableItem.hpp"

ThrowableItem::ThrowableItem(int radius, const std::string &name, const std::string &description, int x, int y, int z, char symbol)
    : radius(radius), Item(name, description, x, y, z, symbol)
{
}

bool ThrowableItem::canBeUsedOnEnemies() const
{
    return true;
}