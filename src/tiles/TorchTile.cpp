//
// Created by pakamaka345 on 1/5/25.
//

#include "TorchTile.hpp"
#include <states/GameState.hpp>
#include <map/Map.hpp>

TorchTile::TorchTile(int radius, int x, int y, int z)
	: InteractTile(TileType::TORCH, x, y, z, '!'), radius(radius), isLit(false)
{
}

void TorchTile::onInteract(GameState& gameState)
{
	const auto map = gameState.getCurrentLevel().getMap();
	for (int dx = getX() - radius; dx <= getX() + radius; dx++) {
		for (int dy = getY() - radius; dy <= getY() + radius; dy++) {
			if (map->isInsideMap(dx, dy)) {
				if (map->getLightType(dx, dy) != LightType::STATIC) {
					map->setLightMap(dx, dy, LightType::STATIC);
				}
			}
		}
	}
}
