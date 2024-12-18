#include "tiles/Tile.hpp"
#include "entities/Entity.hpp"
#include "items/Item.hpp"
#include <iostream>
#include <utility>

Tile::Tile()
    : entity(nullptr), items(), tileType(TileType::Type::EMPTY)
    , GameObject(0, 0, ' ')
{
}

Tile::Tile(int x, int y, char symbol)
    : entity(nullptr), items(), tileType(TileType::Type::EMPTY)
    , GameObject(x, y, symbol)
{
}

Tile::Tile(int x, int y)
    : entity(nullptr), items(), tileType(TileType::Type::EMPTY)
    , GameObject(x, y, '.')
{
}

Tile::Tile(TileType::Type tileType, int x, int y, char symbol)
    : entity(nullptr), items(), tileType(tileType)
    , GameObject(x, y, symbol)
{
}

void Tile::setEntity(std::shared_ptr<Entity> entity) {
    if (!hasEntity()) {
        this->entity = std::move(entity);
    } else {
        throw std::runtime_error("Tile already has an entity");
    }
}

std::shared_ptr<Entity>& Tile::getEntity() {
    return entity;
}

void Tile::removeEntity() {
    if (hasEntity()) {
        entity = nullptr;
    }
}

bool Tile::hasEntity() {
    return entity != nullptr;
}

void Tile::addItem(const std::shared_ptr<Item>& item) {
    items.push_back(item);
}

void Tile::addItems(std::list<std::shared_ptr<Item>> items) {
    this->items.insert(this->items.end(), items.begin(), items.end());
}

std::list<std::shared_ptr<Item>>& Tile::getItems() {
    return items;
}

std::shared_ptr<Item>& Tile::getItem() {
    return items.front();
}

void Tile::removeItem() {
    return items.pop_front();
}

bool Tile::hasItems() {
    return !items.empty();
}

TileType::Type Tile::getTileType() {
    return tileType;
}

void Tile::setTileType(TileType::Type tileType) {
    this->tileType = tileType;
}

bool Tile::isWalkable() const {
    return false;
}