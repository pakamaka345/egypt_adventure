#pragma once
#include "TileType.hpp"
#include "entities/Entity.hpp"
#include "items/Item.hpp"
#include <memory>


class Tile
{
private:
    std::unique_ptr<Entity> entity;
    std::unique_ptr<Item> item;
    TileType::TileType TileType;
    char symbol;

public:
    Tile();
    Tile(TileType::TileType TileType);
    ~Tile() = default;

    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;

    Tile(Tile&&) noexcept = default;
    Tile& operator=(Tile&&) noexcept = default;

    void setEntity(std::unique_ptr<Entity> entity);
    void setItem(std::unique_ptr<Item> item);

    std::unique_ptr<Entity> getEntity();
    std::unique_ptr<Item> getItem();

    TileType::TileType getTileType();
    void setTileType(TileType::TileType TileType);

    bool hasEntity();
    bool hasItem();

    void removeEntity();
    void removeItem();

    virtual char getSymbol();

    virtual bool isWalkable();

    virtual void draw();

private:
    virtual void setSymbol(TileType::TileType TileType);
};