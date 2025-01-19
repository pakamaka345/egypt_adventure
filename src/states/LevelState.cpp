#include "states/LevelState.hpp"
#include "entities/Entity.hpp"
#include "map/Map.hpp"

LevelState::LevelState(std::shared_ptr<Map> map) : map(std::move(map))
{
}

LevelState::LevelState(std::shared_ptr<Map> map, const Position &startPosition)
    : map(std::move(map)), startPosition(startPosition)
{}

void LevelState::update(GameState& gameState) {
    for (const auto& entity : entities) {
        entity->update(gameState);
    }
}







