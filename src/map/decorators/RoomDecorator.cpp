//
// Created by pakamaka345 on 1/5/25.
//

#include "RoomDecorator.hpp"

#include <map/Map.hpp>

#include "map/RoomGenerator.hpp"

RoomDecorator::RoomDecorator(int minRoomSize, int levelIndex)
	: MapDecorator(levelIndex), minRoomSize(minRoomSize)
{
}

void RoomDecorator::decorate(Map& map)
{
	RoomGenerator roomGen;
	roomGen.generateRooms(map.getLeaves(), map, minRoomSize, levelIndex);

	auto& rooms = roomGen.getRooms();
	map.setRooms(rooms);
}

