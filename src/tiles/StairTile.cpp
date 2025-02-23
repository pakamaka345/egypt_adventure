//
// Created by pakamaka345 on 12/27/24.
//

#include "StairTile.hpp"
#include "map/Map.hpp"
#include <entities/Character.hpp>
#include <states/GameState.hpp>

StairTile::StairTile(StairType stairType, int x, int y, int z)
	: stairType(stairType), InteractTile("Stairs", TileType::STAIRS, x, y, z, stairType == StairType::UP ? '>' : '<')
{
}


StairType StairTile::getStairType() const
{
	return stairType;
}

void StairTile::onInteract(GameState& gameState)
{
	gameState.getCurrentLevel().setStartPosition(gameState.getPlayer()->getPos());
	gameState.getCurrentLevel().removeEntity(gameState.getPlayer());
	gameState.getCurrentLevel().getMap()->removeEntity(gameState.getPlayer()->getX(), gameState.getPlayer()->getY());
	int levelIndex = gameState.getLevelIndex();
	gameState.getPlayer()->deleteLight(gameState.getPlayer()->getX(), gameState.getPlayer()->getY(), gameState);
	if (stairType == StairType::UP) {
		gameState.nextLevel(levelIndex + 1);
	} else {
		gameState.nextLevel(levelIndex - 1);
	}
}

bool StairTile::isWalkable() const
{
	return true;
}



