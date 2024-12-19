#include "states/LevelState.hpp"
#include "entities/Entity.hpp"
#include "Map.hpp"

LevelState::LevelState(const Map& map, const LevelState::Position &startPosition)
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

const LevelState::Position &LevelState::getStartPosition() {
    return startPosition;
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




