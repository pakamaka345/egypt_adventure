//
// Created by pakamaka345 on 12/27/24.
//

#include "StairTile.hpp"
#include "GameObject.hpp"

StairTile::StairTile(StairType stairType, int x, int y)
	: stairType(stairType), InteractTile(TileType::STAIRS, x, y, stairType == StairType::UP ? '>' : '<')
{
}


StairType StairTile::getStairType() const
{
	return stairType;
}

void StairTile::onInteract()
{
	// TODO: Implement after with Command Pattern
}

bool StairTile::isWalkable() const
{
	return true;
}



