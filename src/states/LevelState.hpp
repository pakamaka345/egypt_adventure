#pragma once
#include <memory>
#include <list>
#include "GameObject.hpp"

class Map;
class Entity;
class Item;


class LevelState {

private:
    std::shared_ptr<Map> map;
    std::list<std::shared_ptr<Entity>> entities;
    std::list<std::shared_ptr<Item>> items;
    Position startPosition;

public:
    LevelState(const std::shared_ptr<Map>& map);
    LevelState(const std::shared_ptr<Map>& map, const Position& startPosition);
    ~LevelState() = default;

    void update();

    std::shared_ptr<Map> getMap() { return map; }
    const Position& getStartPosition() { return startPosition; }
    void setStartPosition(const Position& position) { startPosition = position; }

    void addEntity(const std::shared_ptr<Entity>& entity) { entities.push_back(entity); }
    void addItem(const std::shared_ptr<Item>& item) { items.push_back(item); }

    std::list<std::shared_ptr<Entity>>& getEntities() { return entities; }
    std::list<std::shared_ptr<Item>>& getItems() { return items; }
};