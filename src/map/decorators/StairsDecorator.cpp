//
// Created by pakamaka345 on 1/5/25.
//

#include "StairsDecorator.hpp"
#include "tiles/StairTile.hpp"
#include <map/Map.hpp>

StairsDecorator::StairsDecorator(int levelIndex)
	: levelIndex(levelIndex)
{
}


void StairsDecorator::decorate(Map& map)
{
	if (levelIndex != 1) {
		auto& firstRoom = map.getRooms().front();
		Position stair1 = firstRoom->getCenter();
		Position start = map.getRandomFreePosition(stair1.x, stair1.y, 3);
		if (start.x != -1 && start.y != -1) {
			map.setTile(std::make_shared<StairTile>(StairType::UP, start.x, start.y));
		}
	}

	auto& lastRoom = map.getRooms().back();
	Position stair2 = lastRoom->getCenter();
	Position end = map.getRandomFreePosition(stair2.x, stair2.y, 3);
	if (end.x != -1 && end.y != -1) {
		map.setTile(std::make_shared<StairTile>(StairType::DOWN, end.x, end.y));
	}
}
