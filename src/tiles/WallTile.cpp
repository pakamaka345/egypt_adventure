#include "tiles/WallTile.hpp"

WallTile::WallTile(int x, int y, int z)
    : Tile(TileType::Type::WALL, x, y, z, '#')
{
}

bool WallTile::isWalkable() const {
    return false;
}