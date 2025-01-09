//
// Created by pakamaka345 on 1/8/25.
//

#include "ItemDecorator.hpp"
#include <dice/DiceRoll.hpp>
#include <items/Item.hpp>
#include <map/Map.hpp>
#include <states/LevelState.hpp>


ItemDecorator::ItemDecorator(int maxItemPerRoom, bool isUnique, std::shared_ptr<Item> item, std::shared_ptr<LevelState> levelState)
	: maxItemPerRoom(maxItemPerRoom), isUnique(isUnique), item(item), levelState(levelState)
{
}

void ItemDecorator::decorate(Map& map)
{
	DiceRoll gen;
	auto& rooms = map.getRooms();
	if (isUnique) {
		int roomIndex = gen.randomNumber(1, rooms.size() - 1);
		auto& room = rooms[roomIndex];
		placeItem(map, room);
	} else {
		for (int i = 1; i < rooms.size(); i++) {
			auto& room = rooms[i];
			int itemPerRoom = gen.randomNumber(1, maxItemPerRoom);
			for (int j = 0; j < itemPerRoom; j++) {
				placeItem(map, room);
			}
		}
	}
}

void ItemDecorator::placeItem(Map& map, const std::shared_ptr<RoomGenerator::Room>& room)
{
	auto pos = map.getRandomFreePosition(room->getCenter().x, room->getCenter().y, 7);

	if (pos != Position(-1, -1)) {
		item->setPos(pos);
		map.placeItem(pos.x, pos.y, item);
		levelState->addItem(item);
	}
}

