//
// Created by pakamaka345 on 1/5/25.
//

#include "TorchTile.hpp"

TorchTile::TorchTile(int radius, int x, int y)
	: InteractTile(TileType::TORCH, x, y, '!'), radius(radius), isLit(false)
{
}

void TorchTile::onInteract()
{
	//TODO: Implement
}
