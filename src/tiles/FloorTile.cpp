#include "tiles/FloorTile.hpp"

FloorTile::FloorTile(int x, int y, int z)
    : Tile(TileType::Type::FLOOR, x, y, z, '.')
{
}

bool FloorTile::isWalkable() const {
    return true;
}