#include "tiles/FloorTile.hpp"

FloorTile::FloorTile(int x, int y)
    : Tile(TileType::Type::FLOOR, x, y, ' ')
{
}

bool FloorTile::isWalkable() const {
    return true;
}