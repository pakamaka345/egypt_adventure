//
// Created by pakamaka345 on 12/27/24.
//

#pragma once
#include "map/RoomGenerator.hpp"

class CorridorGenerator {
public:
	void connectRooms(RoomGenerator::Room& room1, RoomGenerator::Room& room2, Map& map, int levelIndex);

};


