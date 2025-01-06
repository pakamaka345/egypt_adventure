//
// Created by pakamaka345 on 1/5/25.
//

#include "CorridorDecorator.hpp"

#include <map/Map.hpp>

#include "map/CorridorGenerator.hpp"

void CorridorDecorator::decorate(Map& map)
{
	auto& rooms = map.getRooms();
	CorridorGenerator corridorGen;
	for (int i = 1; i < rooms.size(); ++i) {
		corridorGen.connectRooms(*rooms[i - 1], *rooms[i], map);
	}
}
