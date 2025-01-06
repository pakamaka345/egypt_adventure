#pragma once
#include <memory>
#include <list>
#include "GameObject.hpp"

class Map;
class Entity;
class Item;


class LevelState {

private:
    std::unique_ptr<Map> map;
    std::list<std::shared_ptr<Entity>> entities;
    std::list<std::shared_ptr<Item>> items;
    Position startPosition;

public:
    LevelState(const Map& map);
    LevelState(const Map& map, const Position& startPosition);
    ~LevelState() = default;

    void update();

    Map& getMap();
    const Position& getStartPosition();
    void setStartPosition(const Position& position);

    void addEntity(const std::shared_ptr<Entity>& entity);
    void addItem(const std::shared_ptr<Item>& item);

    std::list<std::shared_ptr<Entity>>& getEntities();
    std::list<std::shared_ptr<Item>>& getItems();
};