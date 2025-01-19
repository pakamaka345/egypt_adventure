#pragma once
#include <memory>
#include <list>
#include "utils/GameObject.hpp"

class GameState;
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
    explicit LevelState(std::shared_ptr<Map> map);
    LevelState(std::shared_ptr<Map> map, const Position& startPosition);
    ~LevelState() = default;

    void update(GameState& gameState);

    std::shared_ptr<Map> getMap() { return map; }
    [[nodiscard]] const Position& getStartPosition() const { return startPosition; }
    void setStartPosition(const Position& position) { startPosition = position; }

    void addEntity(const std::shared_ptr<Entity>& entity) { entities.push_back(entity); }
    void addItem(const std::shared_ptr<Item>& item) { items.push_back(item); }

    std::list<std::shared_ptr<Entity>>& getEntities() { return entities; }
    std::list<std::shared_ptr<Item>>& getItems() { return items; }
};