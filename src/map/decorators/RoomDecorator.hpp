//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "MapDecorator.hpp"

class RoomDecorator : public MapDecorator {
	int minRoomSize;

public:
	RoomDecorator(int minRoomSize);

	void decorate(Map& map) override;
};



