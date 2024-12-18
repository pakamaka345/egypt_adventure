#pragma once
#include "GameObject.hpp"
#include <memory>
#include <list>

class Entity;
class Item;

class Tile : public GameObject
{
private:
    std::shared_ptr<Entity> entity;
    std::list<std::shared_ptr<Item>> items;
    TileType::Type tileType;

public:
    Tile();
    Tile(int x, int y, char symbol);
    Tile(int x, int y);
    Tile(TileType::Type tileType, int x, int y, char symbol);
    ~Tile() override = default;

    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;

    Tile(Tile&&) noexcept = default;
    Tile& operator=(Tile&&) noexcept = default;

    void setEntity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity>& getEntity();
    void removeEntity();
    bool hasEntity();

    void addItem(const std::shared_ptr<Item>& item);
    void addItems(std::list<std::shared_ptr<Item>> items);
    std::list<std::shared_ptr<Item>>& getItems();
    std::shared_ptr<Item>& getItem();
    void removeItem();
    bool hasItems();

    TileType::Type getTileType();
    void setTileType(TileType::Type tileType);
    virtual bool isWalkable() const;
};