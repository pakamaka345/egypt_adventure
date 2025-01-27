#include "tiles/Tile.hpp"
#include "entities/Entity.hpp"
#include "items/Item.hpp"
#include <iostream>
#include <utility>

Tile::Tile()
    : entity(nullptr), items(), tileType(TileType::Type::EMPTY)
    , GameObject(0, 0, 0, ' ')
{
}

Tile::Tile(int x, int y, int z, char symbol)
    : entity(nullptr), items(), tileType(TileType::Type::EMPTY)
    , GameObject(x, y, z, symbol)
{
}

Tile::Tile(int x, int y, int z)
    : entity(nullptr), items(), tileType(TileType::Type::EMPTY)
    , GameObject(x, y, z, '.')
{
}

Tile::Tile(TileType::Type tileType, int x, int y, int z, char symbol)
    : entity(nullptr), items(), tileType(tileType)
    , GameObject(x, y, z, symbol)
{
}

void Tile::setEntity(std::shared_ptr<Entity> entity) {
    if (!hasEntity()) {
        this->entity = std::move(entity);
    } else {
        throw std::runtime_error("Tile already has an entity");
    }
}

std::shared_ptr<Entity> Tile::getEntity() {
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

void Tile::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

void Tile::addItems(std::list<std::shared_ptr<Item>> items) {
    this->items.insert(this->items.end(), items.begin(), items.end());
}

std::list<std::shared_ptr<Item>>& Tile::getItems() {
    return items;
}

std::shared_ptr<Item> Tile::getItem() {
    return items.front();
}

std::shared_ptr<Item> Tile::removeItem() {
    auto item = items.front();
    items.pop_front();
    return item;
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