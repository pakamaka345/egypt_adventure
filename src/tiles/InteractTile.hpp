//
// Created by pakamaka345 on 1/5/25.
//

#pragma once
#include "tiles/Tile.hpp"

class InteractTile : public Tile {
public:
	using Tile::Tile;

	virtual void onInteract() = 0;
};



