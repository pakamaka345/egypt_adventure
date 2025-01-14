#include "tiles/SandTile.hpp"

SandTile::SandTile(int x, int y)
    : Tile(TileType::SAND, x, y, '~')
{}

bool SandTile::isWalkable() const {
    return true;
}