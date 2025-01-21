//
// Created by pakamaka345 on 1/19/25.
//

#include "MoveCommand.hpp"

#include <map/Map.hpp>
#include <states/GameState.hpp>
#include <utility>

#include "entities/Entity.hpp"

MoveCommand::MoveCommand(const Direction direction, std::shared_ptr<Entity> entity)
	: direction(direction), entity(std::move(entity))
{
}

void MoveCommand::execute(GameState& gameState)
{
	if (
			const auto offset = getDirectionOffset(direction);
			gameState.getCurrentLevel().getMap()->canPlaceEntity(entity->getX() + offset.x, entity->getY() + offset.y)
		) {
		gameState.getCurrentLevel().getMap()->removeEntity(entity->getX(), entity->getY());
		entity->move(offset.x, offset.y);
		gameState.getCurrentLevel().getMap()->placeEntity(entity->getX(), entity->getY(), entity);
	}
}

Position MoveCommand::getDirectionOffset(const Direction direction)
{
	switch (direction) {
		case Direction::UP: return {0, -1};
		case Direction::DOWN: return {0, 1};
		case Direction::LEFT: return {-1, 0};
		case Direction::RIGHT: return {1, 0};
		default: return {0, 0};
	}
}

