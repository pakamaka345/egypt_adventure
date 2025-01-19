//
// Created by pakamaka345 on 12/27/24.
//

#include "CorridorGenerator.hpp"
#include "map/Map.hpp"
#include "dice/DiceRoll.hpp"
#include "tiles/FloorTile.hpp"

void CorridorGenerator::connectRooms(RoomGenerator::Room& room1, RoomGenerator::Room& room2, Map& map, int levelIndex)
{
	DiceRoll gen;
	std::vector<RoomGenerator::Room> halls;

	Position point1(gen.randomNumber(room1.x + 1, room1.width + room1.x - 2), gen.randomNumber(room1.y + 1, room1.height + room1.y - 2));
	Position point2(gen.randomNumber(room2.x + 1, room2.width + room2.x - 2), gen.randomNumber(room2.y + 1, room2.height + room2.y - 2));

	int w = point2.x - point1.x;
	int h = point2.y - point1.y;

	if (w < 0) {
		if (h < 0) {
			if (gen.randomNumber(0, 1) == 0) {
				halls.emplace_back(point2.x, point1.y, abs(w), 1);
				halls.emplace_back(point2.x, point2.y, 1, abs(h));
			} else {
				halls.emplace_back(point2.x, point2.y, abs(w), 1);
				halls.emplace_back(point1.x, point2.y, 1, abs(h));
			}
		} else if (h > 0) {
			if (gen.randomNumber(0, 1) == 0) {
				halls.emplace_back(point2.x, point1.y, abs(w), 1);
				halls.emplace_back(point2.x, point1.y, 1, abs(h));
			} else {
				halls.emplace_back(point2.x, point2.y, abs(w), 1);
				halls.emplace_back(point1.x, point1.y, 1, abs(h));
			}
		} else {
			halls.emplace_back(point2.x, point2.y, abs(w), 1);
		}
	} else if (w > 0) {
		if (h < 0) {
			if (gen.randomNumber(0, 1) == 0) {
				halls.emplace_back(point1.x, point2.y, abs(w), 1);
				halls.emplace_back(point1.x, point2.y, 1, abs(h));
			} else {
				halls.emplace_back(point1.x, point1.y, abs(w), 1);
				halls.emplace_back(point2.x, point2.y, 1, abs(h));
			}
		} else if (h > 0) {
			if (gen.randomNumber(0, 1) == 0) {
				halls.emplace_back(point1.x, point1.y, abs(w), 1);
				halls.emplace_back(point2.x, point1.y, 1, abs(h));
			} else {
				halls.emplace_back(point1.x, point2.y, abs(w), 1);
				halls.emplace_back(point1.x, point1.y, 1, abs(h));
			}
		} else {
			halls.emplace_back(point1.x, point1.y, abs(w), 1);
		}
	} else {
		if (h < 0) {
			halls.emplace_back(point2.x, point2.y, 1, abs(h));
		} else {
			halls.emplace_back(point1.x, point1.y, 1, abs(h));
		}
	}

	for (auto& hall : halls) {
		for (int y = hall.y; y < hall.y + hall.height; y++) {
			for (int x = hall.x; x <= hall.x + hall.width; x++) {
				if (map.getTile(x, y)->getTileType() != TileType::BEDROCK) {
					map.setTile(std::make_shared<FloorTile>(x, y, levelIndex));
				}
			}
		}
	}
}
