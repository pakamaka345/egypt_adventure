//
// Created by pakamaka345 on 12/27/24.
//

#pragma once
#include "tiles/InteractTile.hpp"

class GameState;

enum class StairType
{
	UP,
	DOWN
};

class StairTile : public InteractTile {
private:
	StairType stairType;

public:
	StairTile(StairType stairType, int x, int y);

	StairType getStairType() const;

	void onInteract() override;

	bool isWalkable() const override;
};
