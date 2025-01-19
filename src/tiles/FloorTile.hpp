#pragma once
#include "tiles/Tile.hpp"

class FloorTile : public Tile {
public:
    FloorTile(int x, int y, int z);
    ~FloorTile() override = default;

    bool isWalkable() const override;
};