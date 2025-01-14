//
// Created by pakamaka345 on 1/5/25.
//

#include "TorchTile.hpp"
#include <states/GameState.hpp>
#include <map/Map.hpp>

TorchTile::TorchTile(int radius, int x, int y)
	: InteractTile(TileType::TORCH, x, y, '!'), radius(radius), isLit(false)
{
}

void TorchTile::onInteract()
{
	auto map = GameState::getInstance().getCurrentLevel().getMap();
	for (int dx = getX() - radius; dx <= getX() + radius; dx++) {
		for (int dy = getY() - radius; dy <= getY() + radius; dy++) {
			if (map->isInsideMap(dx, dy)) {
				auto lightType = map->getLightType(dx, dy);
				if (lightType != LightType::STATIC) {
					map->setLightMap(dx, dy, LightType::STATIC);
				}
			}
		}
	}
}
