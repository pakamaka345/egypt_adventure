#include <utility>

#include "items/Item.hpp"

Item::Item(std::string& name, std::string& description, int x, int y, char symbol)
    : name(name), description(description), GameObject(x, y, symbol)
{
}

std::string& Item::getName() {
    return name;
}

std::string& Item::getDescription() {
    return description;
}

bool Item::canBePlacedOn(TileType::TileType tileType) const {
    return tileType == TileType::TileType::FLOOR;
}






