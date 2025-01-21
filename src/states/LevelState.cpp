#include "states/LevelState.hpp"
#include "entities/Entity.hpp"
#include "map/Map.hpp"

LevelState::LevelState(std::shared_ptr<Map> map) : map(std::move(map))
{
}

LevelState::LevelState(std::shared_ptr<Map> map, const Position &startPosition)
    : map(std::move(map)), startPosition(startPosition)
{}

void LevelState::update(GameState& gameState) const {
    for (const auto& entity : entities) {
        entity->update(gameState);
    }
}

void LevelState::removeEntity(const std::shared_ptr<Entity>& entity)
{
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void LevelState::removeItem(const std::shared_ptr<Item>& item)
{
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}









