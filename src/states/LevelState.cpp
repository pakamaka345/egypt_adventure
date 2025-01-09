#include "states/LevelState.hpp"
#include "entities/Entity.hpp"
#include "map/Map.hpp"

LevelState::LevelState(const std::shared_ptr<Map>& map) : map(map)
{
}

LevelState::LevelState(const std::shared_ptr<Map>& map, const Position &startPosition)
    : map(map), startPosition(startPosition)
{}

void LevelState::update() {
    for (auto& entity : entities) {
        entity->update();
    }
}







