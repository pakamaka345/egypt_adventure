#include "BedrockTile.hpp"

BedrockTile::BedrockTile(int x, int y)
    : Tile(TileType::BEDROCK, x, y, 'X')
{
}

bool BedrockTile::isWalkable() const
{
    return false;
}

