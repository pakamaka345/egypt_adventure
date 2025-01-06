#include "states/LevelState.hpp"
#include "entities/Entity.hpp"
#include "map/Map.hpp"

LevelState::LevelState(const Map& map) : map(std::make_unique<Map>(map))
{
}

LevelState::LevelState(const Map& map, const Position &startPosition)
    : map(std::make_unique<Map>(map)), startPosition(startPosition)
{}

Map &LevelState::getMap() {
    return *map;
}

void LevelState::update() {
    for (auto& entity : entities) {
        entity->update();
    }
}

const Position &LevelState::getStartPosition() {
    return startPosition;
}

void LevelState::setStartPosition(const Position& position)
{
    startPosition = position;
}


void LevelState::addEntity(const std::shared_ptr<Entity>& entity) {
    entities.push_back(entity);
}

void LevelState::addItem(const std::shared_ptr<Item>& item) {
    items.push_back(item);
}

std::list<std::shared_ptr<Entity>> &LevelState::getEntities() {
    return entities;
}

std::list<std::shared_ptr<Item>> &LevelState::getItems() {
    return items;
}




