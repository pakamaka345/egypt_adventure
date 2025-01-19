#pragma once
#include "Tile.hpp"


class BedrockTile : public Tile {
public:
    BedrockTile(int x, int y, int z);
    bool isWalkable() const override;
};

