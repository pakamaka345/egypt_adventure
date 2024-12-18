#include "tiles/SandTile.hpp"

SandTile::SandTile(int x, int y)
    : Tile(TileType::SAND, x, y, 's')
{}

bool SandTile::isWalkable() const {
    return true;
}