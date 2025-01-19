#include "items/Item.hpp"

Item::Item(const std::string& name, const std::string& description, int x, int y, int z, char symbol)
    : name(name), description(description), GameObject(x, y, z, symbol)
{
}

bool Item::canBeUsedOnEnemies() const {
    return false;
}

bool Item::isConsumable() const {
    return true;
}

std::string& Item::getName() {
    return name;
}

std::string& Item::getDescription() {
    return description;
}






