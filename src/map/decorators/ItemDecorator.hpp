//
// Created by pakamaka345 on 1/8/25.
//
#pragma once
#include "MapDecorator.hpp"
#include <map/RoomGenerator.hpp>
#include <memory>

class LevelState;
class Item;

class ItemDecorator : public MapDecorator {
private:
	int maxItemPerRoom;
	bool isUnique;
	std::shared_ptr<Item> item;
	std::shared_ptr<LevelState> levelState;

	void placeItem(Map& map, const std::shared_ptr<RoomGenerator::Room>& room);


public:
	ItemDecorator(int maxItemPerRoom, bool isUnique, std::shared_ptr<Item> item, std::shared_ptr<LevelState> levelState);

	void decorate(Map& map) override;
};


