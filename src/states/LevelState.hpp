#pragma once
#include <memory>
#include <list>

class Map;
class Entity;
class Item;


class LevelState {
public:
    struct Position {
        int x;
        int y;

        Position() : x(0), y(0) {}
        Position(int x, int y) : x(x), y(y) {}
        Position(Position const& pos) = default;

        Position& operator=(Position const& pos) = default;
    };

private:
    std::unique_ptr<Map> map;
    std::list<std::shared_ptr<Entity>> entities;
    std::list<std::shared_ptr<Item>> items;
    Position startPosition;

public:
    LevelState(const Map& map, const Position& startPosition);
    ~LevelState() = default;

    void update();

    Map& getMap();
    const Position& getStartPosition();

    void addEntity(const std::shared_ptr<Entity>& entity);
    void addItem(const std::shared_ptr<Item>& item);

    std::list<std::shared_ptr<Entity>>& getEntities();
    std::list<std::shared_ptr<Item>>& getItems();
};