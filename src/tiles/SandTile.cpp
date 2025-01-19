#include "tiles/SandTile.hpp"

SandTile::SandTile(int x, int y, int z)
    : Tile(TileType::SAND, x, y, z, '~')
{}

bool SandTile::isWalkable() const {
    return true;
}