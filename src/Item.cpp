#include "items/Item.hpp"

Item::Item(const std::string& name, const std::string& description, int x, int y, char symbol)
    : name(name), description(description), GameObject(x, y, symbol)
{
}

std::string& Item::getName() {
    return name;
}

std::string& Item::getDescription() {
    return description;
}

bool Item::canBePlacedOn(TileType::Type tileType) const {
    return tileType == TileType::Type::FLOOR;
}






