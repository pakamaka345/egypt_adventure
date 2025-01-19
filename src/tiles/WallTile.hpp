#pragma once
#include "tiles/Tile.hpp"

class WallTile : public Tile {
public:
    WallTile(int x, int y, int z);
    ~WallTile() override = default;
    bool isWalkable() const override;
};