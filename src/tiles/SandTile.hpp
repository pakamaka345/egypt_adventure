#pragma once
#include "tiles/Tile.hpp"

class SandTile : public Tile {
public:
    SandTile(int x, int y, int z);
    ~SandTile() override = default;

    bool isWalkable() const override;
};