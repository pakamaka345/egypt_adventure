//
// Created by pakamaka345 on 1/19/25.
//

#include "MoveCommand.hpp"

#include <map/Map.hpp>
#include <states/GameState.hpp>
#include <utility>

#include "entities/Entity.hpp"

MoveCommand::MoveCommand(const int dx, const int dy, std::shared_ptr<Entity> entity)
	: dx(dx), dy(dy), entity(std::move(entity))
{
}

void MoveCommand::execute(GameState& gameState)
{
	if (gameState.getCurrentLevel().getMap()->canPlaceEntity(entity->getX() + dx, entity->getY() + dy)) {
		gameState.getCurrentLevel().getMap()->removeEntity(entity->getX(), entity->getY());
		entity->move(dx, dy);
		gameState.getCurrentLevel().getMap()->placeEntity(entity->getX(), entity->getY(), entity);
	}
}

