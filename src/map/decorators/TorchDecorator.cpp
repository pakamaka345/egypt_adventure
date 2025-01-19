//
// Created by pakamaka345 on 1/5/25.
//

#include "TorchDecorator.hpp"
#include <dice/DiceRoll.hpp>
#include "map/Map.hpp"
#include "tiles/TorchTile.hpp"
#include <set>

TorchDecorator::TorchDecorator(int levelIndex)
	: MapDecorator(levelIndex)
{
}


void TorchDecorator::decorate(Map& map) {
	auto rooms = map.getRooms();
	std::set<Position> torchPositions;

	for (const auto& room : rooms) {
		placeTorchInRoom(map, room, torchPositions);
	}
}

void TorchDecorator::placeTorchInRoom(Map& map, const std::shared_ptr<RoomGenerator::Room>& room, std::set<Position>& torchPositions)
{
	bool placed = false;

	while (!placed) {
		auto pos = generateTorchPosition(room);

		if (isValidTorchPosition(map, pos, torchPositions)) {
			map.setTile(std::make_shared<TorchTile>(6, pos.x, pos.y, levelIndex));
			torchPositions.insert(pos);
			placed = true;
		}
	}
}

Position TorchDecorator::generateTorchPosition(const std::shared_ptr<RoomGenerator::Room>& room)
{
	Position pos;
	DiceRoll gen;
	int horizontal = gen.randomNumber(0, 1);

	if (horizontal == 0) {
		int left = gen.randomNumber(0, 1);
		pos.x = (left == 0) ? room->x - 1 : room->x + room->width;
		pos.y = gen.randomNumber(room->y + 1, room->y + room->height - 2);
	} else {
		int top = gen.randomNumber(0, 1);
		pos.x = gen.randomNumber(room->x + 1, room->x + room->width - 2);
		pos.y = (top == 0) ? room->y - 1 : room->y + room->height;
	}

	return pos;
}

bool TorchDecorator::isValidTorchPosition(Map& map, Position pos, const std::set<Position>& torchPositions) const
{
	return map.isInsideMap(pos.x, pos.y) &&
	   map.getTile(pos.x, pos.y)->getTileType() == TileType::WALL &&
	   torchPositions.find({pos.x, pos.y}) == torchPositions.end();
}


