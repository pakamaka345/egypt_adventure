#include "BedrockTile.hpp"

BedrockTile::BedrockTile(int x, int y, int z)
    : Tile(TileType::BEDROCK, x, y, z, 'X')
{
}

bool BedrockTile::isWalkable() const
{
    return false;
}

