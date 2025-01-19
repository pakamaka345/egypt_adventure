//
// Created by pakamaka345 on 12/26/24.
//

#pragma once
#include <vector>
#include <memory>
#include "utils/GameObject.hpp"

class Map;
class BSPNode;

class RoomGenerator {
public:
	struct Room
	{
		int x, y, width, height;

		Room(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}

		Position getCenter() const
		{
			return {x + width / 2, y + height / 2};
		}
	};

public:
	void generateRooms(const std::vector<std::shared_ptr<BSPNode>>& nodes, Map& map, int MinRoomSize, int levelIndex);

	std::vector<std::shared_ptr<Room>>& getRooms() { return rooms; }

private:
	std::vector<std::shared_ptr<Room>> rooms;
};


