#pragma once
#include "tiles/Tile.hpp"

class FloorTile : public Tile {
public:
    FloorTile(int x, int y);
    ~FloorTile() override = default;

    bool isWalkable() const override;
};