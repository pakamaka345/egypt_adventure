#include "tiles/WallTile.hpp"

WallTile::WallTile(int x, int y)
    : Tile(TileType::Type::WALL, x, y, '#')
{
}

bool WallTile::isWalkable() const {
    return false;
}