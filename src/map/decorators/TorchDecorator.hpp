//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "MapDecorator.hpp"
#include <set>
#include <memory>
#include <map/RoomGenerator.hpp>

class Position;

class TorchDecorator : public MapDecorator {
public:
	explicit TorchDecorator(int levelIndex);
	void decorate(Map& map) override;

private:
	void placeTorchInRoom(Map& map, const std::shared_ptr<RoomGenerator::Room>& room, std::set<Position>& torchPositions);
	Position generateTorchPosition(const std::shared_ptr<RoomGenerator::Room>& room);
	bool isValidTorchPosition(Map& map, Position pos, const std::set<Position>& torchPositions) const;
};
