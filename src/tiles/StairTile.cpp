//
// Created by pakamaka345 on 12/27/24.
//

#include "StairTile.hpp"

#include <entities/Character.hpp>
#include <states/GameState.hpp>

StairTile::StairTile(StairType stairType, int x, int y, int z)
	: stairType(stairType), InteractTile(TileType::STAIRS, x, y, z, stairType == StairType::UP ? '>' : '<')
{
}


StairType StairTile::getStairType() const
{
	return stairType;
}

void StairTile::onInteract(GameState& gameState)
{
	gameState.getCurrentLevel().setStartPosition(gameState.getPlayer()->getPos());
	int levelIndex = gameState.getLevelIndex();
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



