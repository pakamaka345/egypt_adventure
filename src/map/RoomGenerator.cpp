//
// Created by pakamaka345 on 12/26/24.
//

#include "RoomGenerator.hpp"
#include "map/Map.hpp"
#include "map/BSPNode.hpp"
#include "tiles/FloorTile.hpp"
#include "dice/DiceRoll.hpp"

void RoomGenerator::generateRooms(const std::vector<std::shared_ptr<BSPNode>>& nodes, Map& map, const int MinRoomSize)
{
	DiceRoll gen;
	for (auto& node : nodes) {
		int roomWidth = gen.randomNumber(MinRoomSize, node->width - 2);
		int roomHeight = gen.randomNumber(MinRoomSize, node->height - 2);

		int roomX = gen.randomNumber(1, node->width - roomWidth - 1) + node->x;
		int roomY = gen.randomNumber(1, node->height - roomHeight - 1) + node->y;

		rooms.emplace_back(std::make_shared<Room>(roomX, roomY, roomWidth, roomHeight));

		for (int y = roomY; y < roomY + roomHeight; ++y) {
			for (int x = roomX; x < roomX + roomWidth; ++x) {
				if (map.getTile(x, y)->getTileType() != TileType::BEDROCK) {
					map.setTile(std::make_shared<FloorTile>(x, y));
				}
			}
		}
	}
}
