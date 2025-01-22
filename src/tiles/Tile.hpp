#pragma once
#include "utils/GameObject.hpp"
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

    // for A* algorithm
    // Total cost of the tile (f = g + h)
    float f;
    // Cost from the start tile to this tile
    float g;
    // Cost from this tile to the end tile
    float h;

public:
    Tile();
    Tile(int x, int y, int z, char symbol);
    Tile(int x, int y, int z);
    Tile(TileType::Type tileType, int x, int y, int z, char symbol);
    ~Tile() override = default;

    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;

    Tile(Tile&&) noexcept = default;
    Tile& operator=(Tile&&) noexcept = default;

    void setEntity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> getEntity();
    void removeEntity();
    bool hasEntity();

    void addItem(std::shared_ptr<Item> item);
    void addItems(std::list<std::shared_ptr<Item>> items);
    std::list<std::shared_ptr<Item>>& getItems();
    std::shared_ptr<Item> getItem();
    void removeItem();
    bool hasItems();

    TileType::Type getTileType();
    void setTileType(TileType::Type tileType);
    virtual bool isWalkable() const;

    void resetPathfinding() { f = g = h = 0.0f; }
    void setG(float value) { g = value; }
    void setH(float value) { h = value; }
    void setF(float value) { f = value; }
    float getG() const { return g; }
    float getH() const { return h; }
    float getF() const { return f; }
};